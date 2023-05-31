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
            App() = default;
            ~App() = default;

            int operator()(int ac, char **av);

        protected:
        private:
            void launch();
        
            void launch(const std::string &ip, const std::string &port);

            void printHelp();
            // TODO DisplayModule
            DisplayModule _displayModule;
            // TODO Parser
            Parser _parser;
            // TODO EntityManager
            EntityManager _entityManager;
            NetworkManager _networkManager;
    };
}
