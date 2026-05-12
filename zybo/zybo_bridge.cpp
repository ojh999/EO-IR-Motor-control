#include <boost/asio.hpp>
#include <boost/asio/serial_port.hpp>
#include <chrono>
#include <csignal>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <array>

namespace asio = boost::asio;
using udp = asio::ip::udp;

// ── 프레임 상수 ──
static constexpr uint8_t  FRAME_START    = 0xAA;
static constexpr uint8_t  FRAME_END      = 0x55;
static constexpr size_t   CMD_UDP_LEN    = 8;    // mode(1) + btn(1) + pan(2) + tilt(2) + scan_step(1) + manual_step(1)
static constexpr size_t   CMD_SERIAL_LEN = 11;   // AA + mode + btn + pan(2) + tilt(2) + scan_step + manual_step + CHK + 55
static constexpr size_t   FB_SERIAL_LEN  = 40;   // AA + mode(1) + PAN(18) + TILT(18) + CHK + 55
static constexpr size_t   FB_UDP_LEN     = 36;   // PAN(18) + TILT(18)

static asio::io_context* g_ioc = nullptr;

static void signal_handler(int)
{
    if (g_ioc) g_ioc->stop();
}

static uint8_t calc_checksum(const uint8_t* data, size_t len)
{
    uint8_t sum = 0;
    for (size_t i = 0; i < len; ++i) sum += data[i];
    return sum;
}

static void hex_dump(const char* tag, const uint8_t* data, size_t len)
{
    std::printf("[%s] %zuB |", tag, len);
    for (size_t i = 0; i < len; ++i) std::printf(" %02X", data[i]);
    std::printf("\n");
    std::fflush(stdout);
}

class ZyboBridge
{
public:
    ZyboBridge(asio::io_context& ioc,
               uint16_t udp_port,
               uint16_t feedback_port,
               const std::string& feedback_ip,
               const std::string& serial_dev,
               unsigned int baud)
        : ioc_(ioc),
          udp_socket_(ioc, udp::endpoint(udp::v4(), udp_port)),
          serial_(ioc, serial_dev),
          feedback_port_(feedback_port),
          feedback_ip_fixed_(!feedback_ip.empty())
    {
        serial_.set_option(asio::serial_port_base::baud_rate(baud));
        serial_.set_option(asio::serial_port_base::character_size(8));
        serial_.set_option(asio::serial_port_base::parity(asio::serial_port_base::parity::none));
        serial_.set_option(asio::serial_port_base::stop_bits(asio::serial_port_base::stop_bits::one));
        serial_.set_option(asio::serial_port_base::flow_control(asio::serial_port_base::flow_control::none));

        if (feedback_ip_fixed_) {
            jetson_endpoint_ = udp::endpoint(
                asio::ip::make_address(feedback_ip), feedback_port);
        }

        std::printf("[bridge] UDP listen  : 0.0.0.0:%u\n", udp_port);
        std::printf("[bridge] Serial      : %s @ %u\n", serial_dev.c_str(), baud);
        if (feedback_ip_fixed_) {
            std::printf("[bridge] Feedback to : %s:%u (fixed)\n", feedback_ip.c_str(), feedback_port);
        } else {
            std::printf("[bridge] Feedback to : sender:%u (auto)\n", feedback_port);
        }
        std::fflush(stdout);
    }

    void start()
    {
        start_udp_receive();
        start_serial_receive();
    }

private:
    // ── UDP 수신 → 시리얼 송신 ──
    void start_udp_receive()
    {
        udp_socket_.async_receive_from(
            asio::buffer(udp_rx_buf_), remote_endpoint_,
            [this](boost::system::error_code ec, size_t bytes) {
                if (ec) {
                    if (ec != asio::error::operation_aborted)
                        std::fprintf(stderr, "[UDP RX] error: %s\n", ec.message().c_str());
                    return;
                }

                // raw hex dump
                std::printf("[UDP RX] %zuB from %s:%u |",
                    bytes,
                    remote_endpoint_.address().to_string().c_str(),
                    remote_endpoint_.port());
                for (size_t i = 0; i < bytes; ++i)
                    std::printf(" %02X", udp_rx_buf_[i]);
                std::printf("\n");
                std::fflush(stdout);

                // 송신자 주소 → 피드백 목적지
                if (!feedback_ip_fixed_) {
                    if (!has_jetson_) {
                        std::printf("[bridge] Jetson detected: %s:%u\n",
                            remote_endpoint_.address().to_string().c_str(),
                            feedback_port_);
                        std::fflush(stdout);
                    }
                    jetson_endpoint_ = remote_endpoint_;
                    jetson_endpoint_.port(feedback_port_);
                    has_jetson_ = true;
                }

                if (bytes == CMD_UDP_LEN) {
                    handle_udp_command();
                } else {
                    std::fprintf(stderr, "[UDP RX] unexpected size: %zu\n", bytes);
                }

                start_udp_receive();
            });
    }

    void handle_udp_command()
    {
        // UDP payload (8B):
        // [0]mode [1]btn [2]pan_L [3]pan_H [4]tilt_L [5]tilt_H [6]scan_step [7]manual_step
        uint8_t  mode      = udp_rx_buf_[0];
        uint8_t  btn       = udp_rx_buf_[1];
        uint16_t pan       = udp_rx_buf_[2] | (static_cast<uint16_t>(udp_rx_buf_[3]) << 8);
        uint16_t tilt      = udp_rx_buf_[4] | (static_cast<uint16_t>(udp_rx_buf_[5]) << 8);
        uint8_t  scan_step = udp_rx_buf_[6];
        uint8_t  man_step  = udp_rx_buf_[7];

        auto now = std::chrono::system_clock::now().time_since_epoch();
        auto ms  = std::chrono::duration_cast<std::chrono::milliseconds>(now).count();
        std::printf("[UDP→SER] %lld ms | mode=%u btn=0x%02X pan=%u tilt=%u scan_step=%u manual_step=%u\n",
                    (long long)ms, mode, btn, pan, tilt, scan_step, man_step);

        // 시리얼 프레임 조립 (11B)
        // [0]AA [1]mode [2]btn [3]pan_L [4]pan_H [5]tilt_L [6]tilt_H
        // [7]scan_step [8]manual_step [9]chk(sum[1..8]) [10]55
        std::array<uint8_t, CMD_SERIAL_LEN> frame;
        frame[0]  = FRAME_START;
        frame[1]  = mode;
        frame[2]  = btn;
        frame[3]  = static_cast<uint8_t>(pan  & 0xFF);
        frame[4]  = static_cast<uint8_t>((pan  >> 8) & 0xFF);
        frame[5]  = static_cast<uint8_t>(tilt & 0xFF);
        frame[6]  = static_cast<uint8_t>((tilt >> 8) & 0xFF);
        frame[7]  = scan_step;
        frame[8]  = man_step;
        frame[9]  = calc_checksum(&frame[1], 8);   // sum(byte[1..8])
        frame[10] = FRAME_END;

        hex_dump("SER TX", frame.data(), CMD_SERIAL_LEN);

        asio::async_write(serial_, asio::buffer(frame),
            [](boost::system::error_code ec, size_t) {
                if (ec) std::fprintf(stderr, "[SER TX] error: %s\n", ec.message().c_str());
            });
    }

    // ── 시리얼 수신 → UDP 송신 ──
    void start_serial_receive()
    {
        asio::async_read(serial_, asio::buffer(&serial_byte_, 1),
            [this](boost::system::error_code ec, size_t) {
                if (ec) {
                    if (ec != asio::error::operation_aborted)
                        std::fprintf(stderr, "[SER RX] error: %s\n", ec.message().c_str());
                    return;
                }

                parse_serial_byte(serial_byte_);
                start_serial_receive();
            });
    }

    void parse_serial_byte(uint8_t b)
    {
        // 프레임 수집 중이 아닐 때만 FRAME_START 동기화
        // (페이로드 안의 0xAA 값에 의한 오인식 방지)
        if (ser_rx_idx_ == 0) {
            if (b != FRAME_START) return;   // 시작 바이트 아니면 무시
        }

        ser_rx_buf_[ser_rx_idx_++] = b;

        if (ser_rx_idx_ == FB_SERIAL_LEN) {
            handle_serial_frame();
            ser_rx_idx_ = 0;
        }
    }

    void handle_serial_frame()
    {
        // 경계 검사
        if (ser_rx_buf_[0] != FRAME_START || ser_rx_buf_[FB_SERIAL_LEN - 1] != FRAME_END) {
            std::fprintf(stderr, "[SER RX] boundary error\n");
            ser_rx_idx_ = 0;   // 재동기화
            return;
        }

        // checksum: sum(byte[1..37]) → byte[38]
        uint8_t chk = calc_checksum(&ser_rx_buf_[1], 37);
        if (ser_rx_buf_[38] != chk) {
            std::fprintf(stderr, "[SER RX] checksum error (got=%02X exp=%02X)\n",
                         ser_rx_buf_[38], chk);
            ser_rx_idx_ = 0;   // 재동기화
            return;
        }

        hex_dump("SER RX", ser_rx_buf_.data(), FB_SERIAL_LEN);

        // UDP 전송 페이로드: byte[2..37] = PAN(18) + TILT(18), mode 제외
        std::array<uint8_t, FB_UDP_LEN> fb_data;
        std::memcpy(fb_data.data(), &ser_rx_buf_[2], FB_UDP_LEN);

        uint8_t mode = ser_rx_buf_[1];
        std::printf("[SER→UDP] mode=%u (%zuB, mode excluded)\n", mode, FB_UDP_LEN);

        if (has_jetson_) {
            udp_socket_.async_send_to(asio::buffer(fb_data), jetson_endpoint_,
                [fb_data](boost::system::error_code ec, size_t) {
                    if (ec) {
                        std::fprintf(stderr, "[UDP TX] error: %s\n", ec.message().c_str());
                    } else {
                        hex_dump("UDP TX", fb_data.data(), FB_UDP_LEN);
                    }
                });
        } else {
            std::printf("[SER→UDP] skip: no jetson endpoint\n");
        }
        std::fflush(stdout);
    }

    // ── 멤버 변수 ──
    asio::io_context& ioc_;
    udp::socket udp_socket_;
    asio::serial_port serial_;
    uint16_t feedback_port_;
    bool feedback_ip_fixed_;
    bool has_jetson_{false};

    // UDP
    std::array<uint8_t, 64> udp_rx_buf_{};
    udp::endpoint remote_endpoint_;
    udp::endpoint jetson_endpoint_;

    // Serial
    uint8_t serial_byte_ = 0;
    std::array<uint8_t, FB_SERIAL_LEN> ser_rx_buf_{};
    size_t ser_rx_idx_ = 0;
};

// ── 설정 ──
struct Config
{
    uint16_t    udp_port      = 6000;
    uint16_t    feedback_port = 6001;
    std::string feedback_ip;
    std::string serial_dev    = "/dev/ttyPS1";
    unsigned    baud          = 115200;
};

static Config parse_args(int argc, char** argv)
{
    Config cfg;
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if      (arg == "--udp-port"      && i+1 < argc) cfg.udp_port      = static_cast<uint16_t>(std::stoi(argv[++i]));
        else if (arg == "--feedback-port" && i+1 < argc) cfg.feedback_port = static_cast<uint16_t>(std::stoi(argv[++i]));
        else if (arg == "--feedback-ip"   && i+1 < argc) cfg.feedback_ip   = argv[++i];
        else if (arg == "--serial"        && i+1 < argc) cfg.serial_dev    = argv[++i];
        else if (arg == "--baud"          && i+1 < argc) cfg.baud          = static_cast<unsigned>(std::stoi(argv[++i]));
        else if (arg == "-h" || arg == "--help") {
            std::printf("Usage: %s [--udp-port 6000] [--feedback-ip IP] "
                        "[--feedback-port 6001] [--serial /dev/ttyPS1] [--baud 115200]\n", argv[0]);
            std::exit(0);
        }
    }
    return cfg;
}

int main(int argc, char** argv)
{
    Config cfg = parse_args(argc, argv);

    asio::io_context ioc;
    g_ioc = &ioc;

    std::signal(SIGINT,  signal_handler);
    std::signal(SIGTERM, signal_handler);

    try {
        ZyboBridge bridge(ioc, cfg.udp_port, cfg.feedback_port,
                          cfg.feedback_ip, cfg.serial_dev, cfg.baud);
        bridge.start();
        std::printf("[bridge] Running... (Ctrl+C to stop)\n");
        std::fflush(stdout);
        ioc.run();
    } catch (const std::exception& e) {
        std::fprintf(stderr, "[bridge] Fatal: %s\n", e.what());
        return 1;
    }

    std::printf("[bridge] Exiting\n");
    return 0;
}
