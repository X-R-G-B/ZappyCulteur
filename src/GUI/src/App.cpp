/*
** EPITECH PROJECT, 2023
** zappy gui
** File description:
** app
*/

#include "App.hpp"
#include <ctime>
#include <sstream>
#include "Floor.hpp"
#include "HUD.hpp"
#include "startMenu.hpp"

static const std::string windowName = "ZappyCulteur";

static constexpr unsigned int height = 1080;
static constexpr unsigned int width = 1920;
static constexpr unsigned int framerateLimit = 60;

static const std::string ipFlag = "-h";
static const std::string portFlag = "-p";

static const std::string defaultIp = "ip";
static const std::string defaultPort = "port";
static const std::string MenuEntityID = "startMenu";

namespace GUI {
    App::AppException::AppException(const std::string &msg) : _msg(msg)
    {
    }

    const char *App::AppException::what() const noexcept
    {
        return (_msg.c_str());
    }

    App::App()
        : _lastTime(std::chrono::system_clock::now()),
          _timeSinceLastServerAsk(0)
    {
        _args[ipFlag] = std::string(defaultIp);
        _args[portFlag] = std::string(defaultPort);
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
        if (arg1.empty() || arg2.empty()) {
            throw AppException("Args error : missing arguments");
        }
        _args[flag1] = arg1;
        _args[flag2] = arg2;
        if (_args[ipFlag] == defaultIp || _args[portFlag] == defaultPort) {
            throw AppException("Args error : flags may be undefined");
        }
    }

    void App::launchUserConnectionMenu()
    {
        auto startMenu = std::make_shared<GUI::Entities::startMenu>();

        _entityManager->killAllEntities();
        _entityManager->addEntity(startMenu);
        while (startMenu->isGameStarted() == false) {
            _entityManager->update(_deltatime);
            _displayModule->handleEvents(_deltatime);
            _displayModule->update(_deltatime);
        }
        _networkManager.initConnection(startMenu->getIP(), startMenu->getPort());
        _entityManager->killEntityById(MenuEntityID);
    }

    void App::launchApp()
    {
        try {
            initModules();
        } catch (const std::exception &err) {
            throw AppException(err.what());
        }
        if (_networkManager.isConnected() == false) {
            launchUserConnectionMenu();
        }
        createHUD();
        gameLoop();
    }

    void App::createHUD()
    {
        _entityManager->addEntity(
        std::make_shared<GUI::Entities::HUD>("HUD", _entityManager));
        if (_commandHandler == nullptr || _displayModule == nullptr) {
            throw AppException("Error while initializing app modules");
        }
    }

    // for now, we ask the server for updates every second
    // next, we will ask in function of the time unit of the server
    void App::askNetworkForUpdate()
    {
        std::string currentPlayerId;

        if (_timeSinceLastServerAsk > 1) {
            _networkManager.sendToServer("mct\n");
            for (const auto &id : _entityManager->getPlayersIds()) {
                currentPlayerId = id;
                if (currentPlayerId.find("Player_") != std::string::npos) {
                    currentPlayerId.erase(0, 7);
                }
                _networkManager.sendToServer("ppo " + currentPlayerId + "\n");
            }
            _timeSinceLastServerAsk = 0;
        }
    }

    void App::updateTime()
    {
        auto currentTime = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed = currentTime - _lastTime;
        _deltatime = elapsed.count();
        _lastTime = currentTime;
        _timeSinceLastServerAsk += _deltatime;
    }

    void App::gameLoop()
    {
        while (_displayModule->isOpen()) {
            updateTime();
            if (_networkManager.isConnected() == false) {
                _networkManager.reconnectToServer();
                continue;
            }
            askNetworkForUpdate();
            _networkManager.update();
            _entityManager->update(_deltatime);
            _commandHandler->update(_networkManager.getServerMessages());
            _displayModule->handleEvents(_deltatime);
            _displayModule->update(_deltatime);
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
        _entityManager = std::make_shared<GUI::Entities::EntitiesManager>();
        if (_entityManager == nullptr) {
            throw AppException("Error while creating EntityManager");
        }
        _displayModule = std::make_unique<GUI::SFML>(_entityManager, windowName,
        width, height, framerateLimit, WINDOW_MODE::WINDOWED);
        _commandHandler = std::make_unique<CommandHandler::CommandHandler>(
        _entityManager, _networkManager.getSendToServer());
        std::srand(std::time(nullptr));
    }

    int App::operator()(int ac, const char **av)
    {
        try {
            if (ac != 1) {
                initArgs(av, ac);
                _networkManager.initConnection(_args[ipFlag], _args[portFlag]);
                launchApp();
            } else {
                launchApp();
            }
        } catch (const std::exception &err) {
            std::cerr << err.what() << std::endl;
        }
        return 0;
    }
} // namespace GUI
