/*
** EPITECH PROJECT, 2023
** zappy gui
** File description:
** main
*/

// #include "./window/Window.hpp"
#include "Main.hpp"

namespace GUI {
    // need refactor when DisplayModule, EntityManager and Parser are implemented
    int Main::operator()(int ac, char **av)
    {
        // GUI::Window window;
        // window.createWindow();
        // while (window.isOpen()) {
            // window.clearWindow();
            // window.displayWindow();
            // window.runEvents();
        // }
        return 0;
    }
}

int main(int ac, char **av)
{
    GUI::Main main;
    int returnValue = 0;

    returnValue = main(ac, av);
    return (returnValue);
}
