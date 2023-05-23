/*
** EPITECH PROJECT, 2023
** zappy server global
** File description:
** get_id uniq
*/

#include "zappy.h"

int get_id(void)
{
    static int id = 0;

    return (++id);
}
