/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** command_look_around_utils
*/

#include "trantorien.h"

int get_min_case_sub(int x, int lvl, int size)
{
    int result = 0;

    result = (x - lvl) % size;
    result = (result < 0) ? result + size : result;
    return result;
}

int get_min_case_add(int x, int lvl, int size)
{
    int result = 0;

    result = (x + lvl) % size;
    result = (result < 0) ? result + size : result;
    return result;
}
