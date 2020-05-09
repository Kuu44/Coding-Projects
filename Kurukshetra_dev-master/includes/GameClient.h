//
// Created by samip on 23/1/19.
//

#pragma once
#include <thread>
#include "Global.h"
#include <SFML/Network.hpp>

class GameClient {

public:
    GameClient(const sf::IpAddress& ip, unsigned short port);
    void connection(const sf::IpAddress& ip, unsigned short port);
    struct clientInfo recieveData();
    bool isConnected() { return m_connected; }
    virtual ~GameClient();
    const struct clientInfo &getRecievedData() const;
    void setNotShooting();
    const std::string &getName() const;

private:
    sf::TcpSocket m_socket;
    bool m_connected;
    bool m_running2;
    std::string Name;
    struct clientInfo recievedData;
    std::thread t1;
};
