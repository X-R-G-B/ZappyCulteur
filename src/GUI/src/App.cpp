/*
** EPITECH PROJECT, 2023
** zappy gui
** File description:
** app
*/

// #include "./window/Window.hpp"
#include "App.hpp"

namespace GUI {
    // need refactor when DisplayModule, EntityManager and Parser are implemented

    void App::launch(const std::string &, const std::string &)
    {
        
    }

    void App::launch()
    {

    }

    void App::printHelp()
    {

    }

    int App::operator()(int ac, char **av)
    {
        if (ac == 0) {
            launch();
        } else if (ac == 3) {
            launch(av[1], av[2]);
        } else {
            printHelp();
        }
        return 0;
    }
}
