/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** ServerConnection
*/

#include <iostream>
#include <unistd.h>
#include "ServerConnection.hpp"

namespace Server {

    ServerConnection::ServerConnectionException::ServerConnectionException(const std::string &message)
        : _Msg(message) {}

    const char *ServerConnection::ServerConnectionException::what() const noexcept
    {
        return (_Msg.c_str());
    }

    const std::string ServerConnection::ServerConnectionException::callWhat() const noexcept
    {
        return (std::string(what()));
    }

    ServerConnection::ServerConnection(const std::string &port, const std::string &ip)
        : _Port(port), _Ip(ip)
    {
        _Socket = socket(AF_INET, SOCK_STREAM, 0);
        if (_Socket < 0) {
            throw ServerConnectionException("Socket initialization failed");
        }
        _Addr.sin_port = htons(std::stoul(port));
        _Addr.sin_family = AF_INET;
        _Addr.sin_addr.s_addr = INADDR_ANY;
        if (connect(_Socket, (struct sockaddr *)&_Addr, sizeof(struct sockaddr))) {
            throw ServerConnectionException("Connection failed");
        }
    }

    ServerConnection::~ServerConnection()
    {
        if (_Socket > 0) {
            close(_Socket);
        }
    }

    void ServerConnection::sendCommand(const std::string &command)
    {
        write(_Socket, command.c_str(), command.size());
    }

    bool ServerConnection::isConnected()
    {
        return (_Socket);
    }

    void ServerConnection::receive()
    {
        int bytes = 0;

        bytes = read(_Socket, _Buffer.data(), BUFFER_SIZE);
        if (bytes < 0) {
            throw ServerConnectionException("Failed to read");
        } else if (bytes == 0) {
            close(_Socket);
            _Socket = 0;
        }
    }

    void ServerConnection::update()
    {
        FD_ZERO(&_Rfds);
        FD_ZERO(&_Wfds);
        FD_ZERO(&_Efds);
        FD_SET(_Socket, &_Rfds);
        FD_SET(_Socket, &_Wfds);
        FD_SET(_Socket, &_Efds);
        if (select(_Socket + 1, &_Rfds, &_Wfds, &_Efds, 0) < 0) {
            throw ServerConnectionException("Failed to select");
        }
        if (FD_ISSET(_Socket, &_Efds)) {
            throw ServerConnectionException("Error detected");
        }
        if (FD_ISSET(_Socket, &_Rfds)) {
            receive();
        }
    }
}
