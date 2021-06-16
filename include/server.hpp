#pragma once
#include <SFML/Network.hpp>
#include <memory>
#include <vector>


class Server
{
public:
  Server();
private:
  sf::IpAddress ip;
  uint16_t port;
  sf::TcpListener listener;
  std::vector<std::unique_ptr<sf::TcpSocket>> connections;
};
