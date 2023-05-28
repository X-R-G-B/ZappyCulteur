/*
** EPITECH PROJECT, 2023
** zappy server map
** File description:
** index i to x y
*/

#include <stddef.h>
#include "map.h"

void map_index_i_to_x_y(map_t *map, int i, int *x, int *y)
{
    if (map == NULL || x == NULL || y == NULL) {
        return;
    }
    *y = i / map->width;
    *x = i % map->width;
}

void map_index_x_y_to_i(map_t *map, int x, int y, int *i)
{
    if (map == NULL || i == NULL) {
        return;
    }
    *i = y * map->width + x;
}
