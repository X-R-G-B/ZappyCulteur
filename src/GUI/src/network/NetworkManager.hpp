/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** NetworkManager
*/

#pragma once

#ifdef _WIN32
    #include <ws2tcpip.h>
    #include <winsock2.h>
#else
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <sys/select.h>
    #include <arpa/inet.h>
    #include <sys/types.h>
    #include <string.h>
    #include <unistd.h>
#endif

#include <string>
#include <vector>
#include <iostream>
#include <array>
#include <stdexcept>

namespace Zappy {

    class NetworkManager {

        static constexpr std::size_t BUFFER_SIZE = 1024;

        class NetworkException : public std::exception {
            public:
                NetworkException(const std::string &message);
                const char *what() const noexcept override;

            private:
                std::string _message;
        };

    public:

        NetworkManager(const std::string& ip, const std::string& port);

        ~NetworkManager();

        /**
         * @brief send a data to the server, require update() to be sent
         * 
         * @param data string that end with newline character
         */
        void sendToServer(const std::string& data);

        /**
         * @brief update the connection, send or receive data if needed
         * 
         */
        void update();

        /**
         * @brief init the connection with the server
         * 
         */
        void initConnection();

        /**
         * @brief reconnect to the server if the connection is lost
         * 
         */
        bool reconnectToServer();

        /**
         * @brief get the messages received from the server and clean it from the networkManger
         * @return std::vector<std::string> 
         */
        std::vector<std::string> getServerMessages();

        /**
         * @brief set the ip of the server
         * 
         * @param ip 
         */
        void setIp(const std::string& ip);

        /**
         * @brief set the port of the server
         * 
         * @param port 
         */
        void setPort(const std::string& port);

        /**
         * @brief check if the client is connected to the server
         * 
         * @return true or false
         */
        bool isConnected() const;

        /**
         * @brief close the connection with the server
         * 
         */
        void deconnectFromServer();

    private:

        void clearServerMessages();
        bool connectToServer();
        void addMessagesToVector(std::string &message);
        void receiveData();
        void sendData();
        void updateFds();
        void createSocket();
        void connectSocket();

        // Attributes //

        #ifdef _WIN32
            SOCKET _serverSocket;
            WSADATA _wsa;
        #else 
            int _serverSocket;
        #endif

        fd_set _readfds;
        fd_set _writefds;
        fd_set _exceptfds;
        std::string _ip;
        std::string _port;
        bool _isConnected;
        struct sockaddr_in _addr;
        struct timeval _tv = {0, 0};

        std::vector<std::string> _dataToSend;
        std::vector<std::string> _serverMessages;
    };
}
