#ifndef SENTINEL_MOTOR__UDP_TRANSPORT_HPP_
#define SENTINEL_MOTOR__UDP_TRANSPORT_HPP_

#include "sentinel_motor/PacketDef.hpp"

#include <boost/asio.hpp>

#include <array>
#include <cstdint>
#include <string>

namespace sentinel_motor
{

class UdpTransport
{
public:
  UdpTransport(const std::string & target_ip, uint16_t target_port, uint16_t listen_port);

  void open();
  void send_command(const CommandPacket & command);
  bool receive_feedback(std::array<uint8_t, kFeedbackPacketSize> & out_feedback);

private:
  boost::asio::io_context io_context_;
  boost::asio::ip::udp::socket socket_;
  boost::asio::ip::udp::endpoint target_endpoint_;
  boost::asio::ip::udp::endpoint sender_endpoint_;
  uint16_t listen_port_;
};

}  // namespace sentinel_motor

#endif  // SENTINEL_MOTOR__UDP_TRANSPORT_HPP_
