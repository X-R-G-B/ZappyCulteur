/*
** EPITECH PROJECT, 2023
** zappy gui
** File description:
** app
*/

#include <sstream>
#include <ctime>
#include "App.hpp"

namespace GUI {
    static const std::string windowName = "ZappyCulteur";

    static constexpr std::size_t height = 1080;
    static constexpr std::size_t width = 1920;
    static constexpr unsigned int framerateLimit = 60;

    App::AppException::AppException(const std::string &msg)
        : _msg(msg){}
    
    const char *App::AppException::what() const noexcept
    {
        return (_msg.c_str());
    }

    void App::initArgs(const char **av, int ac)
    {
        std::string params;

        for (int i = 1; i < ac; i++) {
            params.append(std::string(av[i]) + " ");
        }

        std::stringstream paramsStream(params);
        std::string flag1;
        std::string flag2;
        std::string arg1;
        std::string arg2;

        paramsStream >> flag1 >> arg1 >> flag2 >> arg2;

        if (flag1 == "--help" || flag2 == "--help") {
            printHelp();
            throw AppException("Exiting...");
        }
        if (flag1 == "-h") {
            _ip = arg1;
        }
        if (flag1 == "-p") {
            _port = arg1;
        }
        if (flag2 == "-h") {
            _ip = arg2;
        }
        if (flag2 =="-p") {
            _port = arg2;
        }
        if (_port.empty() || _ip.empty()) {
            throw AppException("Args error : flags may be undefined");
        }
    }

    void App::launchUserConnectionMenu()
    {
        std::cout << "Menu will be implemented later." << std::endl;
    }

    void App::launchApp()
    {
        if (!_port.empty() && !_ip.empty()) {
            _networkManager.initConnection(_ip, _port);
            if (_networkManager.isConnected() == false) {
                throw AppException("Connection error. Please check if the server exists.");
            }
        }
        try {
            initModules();
        } catch (const std::exception &err) {
            throw AppException(err.what());
        }
        while (_networkManager.isConnected() == false) {
            launchUserConnectionMenu();
        }
        gameLoop();
    }

    void App::gameLoop()
    {
        while (_displayModule->isOpen()) {
            if (_networkManager.isConnected() == false) {
                _networkManager.reconnectToServer();
                continue;
            }
            _networkManager.update();
            _commandHandler->update(_networkManager.getServerMessages());
            _displayModule->handleEvents();
            _displayModule->update();
        }
    }

    void App::printHelp()
    {
        std::cout << "USAGE: ./zappy_gui -h [ip] -p [port]" << std::endl;
        std::cout << "\tip = ip address of the server" << std::endl;
        std::cout << "\tport = port number of the server" << std::endl;
    }

    void App::initModules()
    {
        _networkManager.sendToServer("GRAPHIC\n");
        _entityManager = std::make_shared<GUI::Entities::EntitiesManager>();
        if (_entityManager == nullptr) {
            throw AppException("Error while creating EntityManager");
        }
        _displayModule = std::make_unique<SFML>(
            _entityManager,
            windowName,
            width,
            height,
            framerateLimit,
            WINDOW_MODE::FULLSCREEN
        );
        _commandHandler = std::make_unique<CommandHandler::CommandHandler>(_entityManager);
        if (_commandHandler == nullptr || _displayModule == nullptr) {
            throw AppException("Error while initializing app modules");
        }
        std::srand(std::time(nullptr));
    }

    int App::operator()(int ac, const char **av)
    {
        if (ac != 1) {
            try {
                initArgs(av, ac);
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
