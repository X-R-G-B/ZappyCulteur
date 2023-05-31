/*
** EPITECH PROJECT, 2023
** zappy gui
** File description:
** app
*/

#include <sstream>
#include "App.hpp"

namespace GUI {
    App::AppException::AppException(const std::string &msg)
        : _msg(msg){}
    
    const char *App::AppException::what() const noexcept
    {
        return (_msg.c_str());
    }

    void App::initArgs(const char **av)
    {
        std::string params;

        for (int i = 1; av[i] != nullptr; i++) {
            params.append(std::string(av[i]) + " ");
        }

        std::stringstream paramsStream(params);
        std::string flag1;
        std::string flag2;
        std::string arg1;
        std::string arg2;

        paramsStream >> flag1 >> arg1 >> flag2 >> arg2;

        if (!strcmp(flag1.c_str(), "-h")) {
            _ip = arg1;
        }
        if (!strcmp(flag1.c_str(), "-p")) {
            _port = arg1;
        }
        if (!strcmp(flag2.c_str(), "-h")) {
            _ip = arg2;
        }
        if (!strcmp(flag2.c_str(), "-p")) {
            _port = arg2;
        }
        if (_port.empty() || _ip.empty()) {
            throw AppException("Args error : flags may be undefined");
        }
    }

    void App::launchUserConnectionMenu()
    {
        // _displayModule.update(ENUM);
        // get input of user
        // connection try
        // return
        std::cout << "Menu will be implemented later." << std::endl;
    }

    void App::launchApp()
    {
        if (!_port.empty() && !_ip.empty()) {
            std::cout << _ip << std::endl;
            std::cout << _port << std::endl;
            _networkManager.initConnection(_ip, _port);
            if (_networkManager.isConnected() == false) {
                throw AppException("Connection error. Please check if the server exists.");
            }
        }
        while (1) {
            if (_networkManager.isConnected() == false) {
                launchUserConnectionMenu();
                continue;
            }
            _networkManager.update();
            for (const auto &elem : _networkManager.getServerMessages()) {
                std::cout << elem << std::endl;
            }
        }
    }

    void App::printHelp()
    {
        std::cout << "Do printHelp" << std::endl;
    }

    int App::operator()(int ac, const char **av)
    {
        if (ac != 1) {
            try {
                initArgs(av);
                launchApp();
            } catch (const std::exception &err) {
                std::cerr << err.what() << std::endl;
            }
        } else {
            launchApp();
        }
        return 0;
    }
}
