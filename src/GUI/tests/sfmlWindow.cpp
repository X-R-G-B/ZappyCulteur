/*
** EPITECH PROJECT, 2023
** zappy gui
** File description:
** main
*/

#include "SFML.hpp"

int main(void)
{
    GUI::SFML sfml(
        nullptr,
        "Zappy bzz bzz",
        1920,
        1080,
        120,
        GUI::WINDOW_MODE::FULLSCREEN
    );

    while (sfml.isOpen()) {
        sfml.handleEvents();
        sfml.update();
    }
    return 0;
}
