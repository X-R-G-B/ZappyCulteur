/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** NetworkManager
*/

#include "NetworkManager.hpp"

namespace Zappy {

    NetworkManager::NetworkException::NetworkException(const std::string &message) :
        _message(message)
    {}
    const char *NetworkManager::NetworkException::what() const noexcept
    { 
        return _message.c_str();
    }

    NetworkManager::NetworkManager(const std::string& ip, const std::string& port) :
        _port(port),
        _isConnected(false)
    {
        setIp(ip);
        try {
            initConnection();
            connectToServer();
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
        }
    }

    NetworkManager::~NetworkManager()
    {
        deconnectFromServer();
        #ifdef _WIN32
            WSACleanup();
        #endif
    }

    void NetworkManager::deconnectFromServer()
    {
        #ifdef _WIN32
            if (_serverSocket != INVALID_SOCKET)
            {
                shutdown(_serverSocket, SD_BOTH);
                closesocket(_serverSocket);
            }
        #else
            if (_serverSocket != -1)
            {
                shutdown(_serverSocket, SHUT_RDWR);
                close(_serverSocket);
            }
        #endif
    }

    void NetworkManager::sendToServer(const std::string& data)
    {
        if (data.empty() == true || data.back() != '\n')
        {
            return;
        }
        _dataToSend.push_back(data);
    }

    void NetworkManager::update()
    {
        if (_isConnected == true)
        {
            updateFds();
            if (select(_serverSocket + 1, &_readfds, nullptr, nullptr, &_tv) == -1)
            {
                throw NetworkException("Error: select failed");
            }
            if (FD_ISSET(_serverSocket, &_readfds))
            {
                receiveData();
            }
            if (_dataToSend.empty() == false)
            {
                sendData();
            }
        }
    }

    std::vector<std::string> NetworkManager::getServerMessages()
    {
        std::vector<std::string> messages = _serverMessages;
        clearServerMessages();
        return messages;
    }

    void NetworkManager::setIp(const std::string& ip)
    {
        if (ip == "localhost")
        {
            _ip = "127.0.0.1";
        }
        else
        {
            _ip = ip;
        }
    }

    void NetworkManager::setPort(const std::string& port)
    {
        _port = port;
    }

    bool NetworkManager::isConnected() const
    {
        return _isConnected;
    }

    void NetworkManager::clearServerMessages()
    {
        _serverMessages.clear();
    }

    bool NetworkManager::connectToServer()
    {
        try {
            createSocket();
            connectSocket();
            _isConnected = true;
        } catch (const std::exception &e) {
            _isConnected = false;
            std::cerr << e.what() << std::endl;
        }
        return _isConnected;
    }

    bool NetworkManager::reconnectToServer()
    {
        if (_isConnected == true)
        {
            return true;
        }
        else
        {
            deconnectFromServer();
            return connectToServer();
        }
    }

    void NetworkManager::initConnection()
    {
        #ifdef _WIN32
            _wsa = {0};
            if (WSAStartup(MAKEWORD(2, 2), &_wsa) != 0)
            {
                throw NetworkException("Error: WSAStartup failed");
            }
        #endif
        _addr.sin_family = AF_INET;
        _addr.sin_port = htons(static_cast<u_short>(std::stoul(_port)));
        _addr.sin_addr.s_addr = inet_addr(_ip.c_str());
    }

    void NetworkManager::createSocket()
    {
        _serverSocket = socket(_addr.sin_family, SOCK_STREAM, IPPROTO_TCP);
        if (_serverSocket == -1)
        {
            throw NetworkException("Error: cannot create socket");
        }
    }

    void NetworkManager::connectSocket()
    {
        if (connect(_serverSocket, reinterpret_cast<struct sockaddr*>(&_addr), sizeof(_addr)) == -1)
        {
            deconnectFromServer();
            throw NetworkException("Error: cannot connect to server");
        }
    }

    void NetworkManager::addMessagesToVector(std::string &message)
    {
        std::size_t pos = 0;
        std::size_t lenght = 0;

        while ((pos = message.find("\n")) != std::string::npos)
        {
            lenght = pos + 1;
            _serverMessages.push_back(message.substr(0, pos));
            message.erase(0, lenght);
        }
    }

    void NetworkManager::receiveData()
    {
        std::string message;
        std::array<char, BUFFER_SIZE> buffer = {0};

        while (true)
        {
            int nbBytes = recv(_serverSocket, buffer.data(), BUFFER_SIZE, 0);
            if (nbBytes <= 0)
            {
                _isConnected = false;
                throw NetworkException("Error: read failed");
            }
            message += std::string(buffer.data(), nbBytes);
            if (message.back() == '\n')
            {
                break;
            }
        }
        addMessagesToVector(message);
    }

    void NetworkManager::sendData()
    {
        std::string toSend = "";
    
        while (_dataToSend.empty() == false)
        {
            toSend = _dataToSend.front();
            if (send(_serverSocket, toSend.c_str(), static_cast<int>(toSend.size()), 0) == -1)
            {
                _isConnected = false;
                throw NetworkException("Error: write failed");
            }
            else
            {
                _dataToSend.erase(_dataToSend.begin());
            }
        }
    }

    void NetworkManager::updateFds()
    {
        FD_ZERO(&_readfds);
        FD_SET(_serverSocket, &_readfds);
    }
}
