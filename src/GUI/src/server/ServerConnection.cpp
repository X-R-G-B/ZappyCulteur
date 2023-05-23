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

    ServerConnection::ServerConnection(const std::string &ip, const std::string &port)
        : _port(port), _ip(ip)
    {
        _socket = socket(AF_INET, SOCK_STREAM, 0);
        if (_socket < 0) {
            throw ServerConnectionException("Socket initialization failed");
        }
        _addr.sin_port = htons(std::stoul(port));
        _addr.sin_family = AF_INET;
        _addr.sin_addr.s_addr = INADDR_ANY;
        if (connect(_socket, (struct sockaddr *)&_addr, sizeof(struct sockaddr))) {
            throw ServerConnectionException("Connection failed");
        }
    }

    ServerConnection::~ServerConnection()
    {
        if (_socket > 0) {
            shutdown(_socket, SHUT_RDWR);
            close(_socket);
        }
    }
    
    const std::string ServerConnection::getResponse()
    {
        return (std::string(_buffer.data()));
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
        int bytes = 0;

        bytes = read(_socket, _buffer.data(), BUFFER_SIZE);
        if (bytes < 0) {
            throw ServerConnectionException("Failed to read");
        } else if (bytes == 0) {
            shutdown(_socket, SHUT_RDWR);
            close(_socket);
            _socket = 0;
        }
    }

    void ServerConnection::sendCommand()
    {
        send(_socket, _toSend.back().c_str(), BUFFER_SIZE, 0);
        _toSend.pop_back();
    }

    void ServerConnection::update()
    {
        struct timeval tv;

        tv.tv_sec = 5;
        tv.tv_usec = 0;
        FD_ZERO(&_rfds);
        FD_ZERO(&_wfds);
        FD_ZERO(&_efds);
        if (_toSend.empty()) {
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
        }
        if (FD_ISSET(_socket, &_wfds)) {
            sendCommand();
        }
    }
}
