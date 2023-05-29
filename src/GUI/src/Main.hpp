/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** Main
*/

#pragma once

#include "EntityManager.hpp"
#include "DisplayModule.hpp"
#include "Parser.hpp"

namespace GUI {
    class Main {
        public:
            Main() = default;
            ~Main() = default;

            int operator()(int ac, char **av);

        protected:
        private:
            // TODO DisplayModule
            DisplayModule _displayModule;
            // TODO Parser
            Parser _parser;
            // TODO EntityManager
            EntityManager _entityManager;
    };
}
