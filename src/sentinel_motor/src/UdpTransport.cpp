#include "sentinel_motor/UdpTransport.hpp"

#include <boost/asio/socket_base.hpp>
#include <boost/system/error_code.hpp>

#include <stdexcept>

namespace sentinel_motor
{

UdpTransport::UdpTransport(
  const std::string & target_ip,
  uint16_t target_port,
  uint16_t listen_port)
: socket_(io_context_),
  target_endpoint_(boost::asio::ip::make_address(target_ip), target_port),
  listen_port_(listen_port)
{
}

void UdpTransport::open()
{
  socket_.open(boost::asio::ip::udp::v4());
  socket_.set_option(boost::asio::socket_base::reuse_address(true));
  socket_.bind(boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), listen_port_));
  socket_.non_blocking(true);
}

void UdpTransport::send_command(const CommandPacket & command)
{
  const auto packet = serialize_command(command);
  const auto bytes_sent = socket_.send_to(boost::asio::buffer(packet), target_endpoint_);

  if (bytes_sent != kCommandPacketSize) {
    throw std::runtime_error("incomplete UDP command packet send");
  }
}

bool UdpTransport::receive_feedback(std::array<uint8_t, kFeedbackPacketSize> & out_feedback)
{
  boost::system::error_code error_code;
  const auto bytes_received = socket_.receive_from(
    boost::asio::buffer(out_feedback),
    sender_endpoint_,
    0,
    error_code);

  if (error_code == boost::asio::error::would_block ||
      error_code == boost::asio::error::try_again) {
    return false;
  }

  if (error_code) {
    throw std::runtime_error("UDP feedback receive failed: " + error_code.message());
  }

  if (bytes_received != kFeedbackPacketSize) {
    throw std::runtime_error("unexpected UDP feedback packet size");
  }

  return true;
}

}  // namespace sentinel_motor
