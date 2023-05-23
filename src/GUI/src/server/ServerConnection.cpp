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
        : _msg(message) {}

    const char *ServerConnection::ServerConnectionException::what() const noexcept
    {
        return (_msg.c_str());
    }

    ServerConnection::ServerConnection(const std::string &ip, const std::string &port)
        : _port(port), _ip(ip)
    {
        socklen_t len = sizeof(struct sockaddr);

        _socket = socket(AF_INET, SOCK_STREAM, 0);
        if (_socket < 0) {
            throw ServerConnectionException("Socket initialization failed");
        }
        _addr.sin_port = htons(std::stoul(port));
        _addr.sin_family = AF_INET;
        _addr.sin_addr.s_addr = INADDR_ANY;
        if (connect(_socket, (struct sockaddr *)&_addr, len) < 0) {
            throw ServerConnectionException("Connection failed");
        }
        isRead = false;
    }

    ServerConnection::~ServerConnection()
    {
        if (_socket > 0) {
            shutdown(_socket, SHUT_RDWR);
            close(_socket);
        }
    }

    const std::vector<std::string> &ServerConnection::getResponses()
    {
        return (_responses);
    }
    
    const std::string ServerConnection::getResponse()
    {
        return (_responses.empty() ? "" : _responses.back());
    }

    void ServerConnection::addCommand(const std::string &command)
    {
        _toSend.push_back(command);
    }

    bool ServerConnection::isConnected()
    {
        return (_socket);
    }

    void ServerConnection::receive()
    {
        std::array<char, BUFFER_SIZE> buffer = {0};
        int bytes = 0;

        bytes = read(_socket, buffer.data(), BUFFER_SIZE);
        if (bytes < 0) {
            throw ServerConnectionException("Failed to read");
        } else if (bytes == 0) {
            shutdown(_socket, SHUT_RDWR);
            close(_socket);
            _socket = 0;
        }
        _responses.push_back(std::string(buffer.data()));
    }

    void ServerConnection::sendCommand()
    {
        if (_toSend.empty()) {
            return;
        }
        write(_socket, _toSend.back().data(), _toSend.back().size());
        _toSend.pop_back();
        isRead = false;
    }

    void ServerConnection::update()
    {
        struct timeval tv;

        tv.tv_sec = 0;
        tv.tv_usec = 0;
        FD_ZERO(&_rfds);
        FD_ZERO(&_wfds);
        FD_ZERO(&_efds);
        if (!isRead) {
            FD_SET(_socket, &_rfds);
        } else {
            FD_SET(_socket, &_wfds);
        }
        FD_SET(_socket, &_efds);
        if (select(_socket + 1, &_rfds, &_wfds, &_efds, &tv) < 0) {
            throw ServerConnectionException("Failed to select");
        }
        if (FD_ISSET(_socket, &_efds)) {
            throw ServerConnectionException("Error detected");
        }
        if (FD_ISSET(_socket, &_rfds)) {
            receive();
            isRead = true;
        }
        if (FD_ISSET(_socket, &_wfds)) {
            sendCommand();
        }
    }
}
