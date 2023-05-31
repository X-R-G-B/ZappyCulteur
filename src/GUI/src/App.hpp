/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** App
*/

#pragma once

#include "EntityManager.hpp"
#include "DisplayModule.hpp"
#include "NetworkManager.hpp"
#include "Parser.hpp"

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

            const std::pair<std::string, std::string> &getArgs();

            const std::pair<std::string, std::string> &getArgs() const;

        protected:
        private:
            void initArgs(const char **av);

            void launchUserConnectionMenu();

            void launchApp();
        
            void printHelp();
            // TODO DisplayModule
            DisplayModule _displayModule;
            // TODO Parser
            Parser _parser;
            // TODO EntityManager
            EntityManager _entityManager;
            NetworkManager _networkManager;
            std::string _port;
            std::string _ip;
    };
}
