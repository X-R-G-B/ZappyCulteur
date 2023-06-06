/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** main
*/

#include "App.hpp"

int main(int ac, const char **av)
{
    GUI::App app;
    int returnValue = 0;

    returnValue = app(ac, av);
    return (returnValue);
}
