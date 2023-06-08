/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** App
*/

#pragma once

#include "IDisplayModule.hpp"
#include "NetworkManager.hpp"
#include "CommandHandler.hpp"
#include "SFML.hpp"
#include "EntitiesManager.hpp"
#include <memory>

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
            App() = default;
            ~App() = default;

            int operator()(int ac, const char **av);

        private:
            void initArgs(const char **av, int ac);
            void launchUserConnectionMenu();
            void launchApp();
            void initModules();
            void gameLoop();
            void printHelp();

            NetworkManager _networkManager;
            std::string _port;
            std::string _ip;
            std::unique_ptr<IDisplayModule> _displayModule;
            std::shared_ptr<GUI::Entities::EntitiesManager> _entityManager;
            std::unique_ptr<CommandHandler::CommandHandler> _commandHandler;
    };
}
