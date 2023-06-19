/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** App
*/

#pragma once

#include <chrono>
#include <memory>
#include "CommandHandler.hpp"
#include "EntitiesManager.hpp"
#include "IDisplayModule.hpp"
#include "NetworkManager.hpp"
#include "SFML.hpp"

namespace GUI {
    class App {
        public:
            class AppException : public std::exception {
                public:
                    AppException(const std::string &msg);
                    ~AppException() = default;

                    const char *what() const noexcept override;

                private:
                    std::string _msg;
            };
            App();
            ~App() = default;

            int operator()(int ac, const char **av);

        private:
            void initArgs(const char **av, int ac);
            void launchUserConnectionMenu();
            void launchApp();
            void initModules();
            void gameLoop();
            void printHelp();
            void askNetworkForUpdate();
            void updateTime();

            NetworkManager _networkManager;
            std::unordered_map<std::string, std::string> _args;
            std::unique_ptr<IDisplayModule> _displayModule;
            std::shared_ptr<GUI::Entities::EntitiesManager> _entityManager;
            std::unique_ptr<CommandHandler::CommandHandler> _commandHandler;
            double _deltatime;
            std::chrono::time_point<std::chrono::system_clock> _lastTime;
            double _timeSinceLastServerAsk;
    };
} // namespace GUI
