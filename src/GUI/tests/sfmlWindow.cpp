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
        "Zappy bzz bzz"
    );

    while (sfml.isOpen()) {
        sfml.handleEvents();
        sfml.update();
    }
    return 0;
}
