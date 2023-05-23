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

    static constexpr std::size_t BUFFER_SIZE = 2048;

    class ServerConnection {
        public:

            class ServerConnectionException : public std::exception {
                public:
                    explicit ServerConnectionException(const std::string &message);

                    const std::string callWhat() const noexcept;
                private:
                    const char *what() const noexcept override;

                    std::string _Msg;
            };

            ServerConnection(const std::string& port, const std::string& ip);
            ~ServerConnection();

            void sendCommand(const std::string &command);

            bool isConnected();

            const std::array<char, BUFFER_SIZE> &getResponse();

            void update();

        protected:
        private:
            void receive();

            std::string _Port;
            std::string _Ip;
            std::vector<std::string> _Tosend;
            std::array<char, BUFFER_SIZE> _Buffer;
            int _Socket;
            fd_set _Rfds;
            fd_set _Wfds;
            fd_set _Efds;
            sockaddr_in _Addr;
    };
}
