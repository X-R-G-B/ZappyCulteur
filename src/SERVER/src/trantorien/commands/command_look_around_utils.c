/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** command_look_around_utils
*/

#include <stddef.h>
#include <stdlib.h>
#include "ntw.h"
#include "zappy.h"
#include "trantorien.h"
#include "map.h"

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
