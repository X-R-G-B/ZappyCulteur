/*
** EPITECH PROJECT, 2023
** zappy gui
** File description:
** main
*/

#include "./window/Window.hpp"

int main(void)
{
    GUI::Window window;

    window.createWindow();
    while (window.isOpen()) {
        window.clearWindow();
        window.displayWindow();
        window.runEvents();
    }
    return 0;
}
