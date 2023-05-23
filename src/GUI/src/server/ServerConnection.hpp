/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** ServerConnection
*/

#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <string>
#include <array>
#include <vector>

#pragma once

namespace Server {

    static constexpr std::size_t BUFFER_SIZE = 2028;

    class ServerConnection {
        public:

            class ServerConnectionException : public std::exception {
                public:
                    explicit ServerConnectionException(const std::string &message);

                    const char *what() const noexcept override;
                private:
                    std::string _Msg;
            };

            ServerConnection(const std::string &ip, const std::string &port);
            ~ServerConnection();

            void addCommand(const std::string &command);


            bool isConnected();

            const std::string getResponse();

            void update();

        protected:
        private:

            void receive();

            void sendCommand();

            std::string _port;
            std::string _ip;
            std::array<char, BUFFER_SIZE> _buffer;
            int _socket;
            std::vector<std::string> _toSend;
            fd_set _rfds;
            fd_set _wfds;
            fd_set _efds;
            sockaddr_in _addr;
    };
}
