/*
** EPITECH PROJECT, 2023
** zappy server map
** File description:
** add ressources
*/

#include <string.h>
#include <stdio.h>
#include "map.h"

static float density[PLAYER] = {
    0.5,
    0.3,
    0.15,
    0.1,
    0.1,
    0.08,
    0.05
};

static void add_ressources(map_tile_t *tile,
    int const nb_step_int[PLAYER],
    int nb_step[PLAYER])
{
    for (int i = 0; i < PLAYER; i++) {
        nb_step[i] -= 1;
        if (nb_step[i] <= 0) {
            tile->ressources[i] += 1;
            nb_step[i] = nb_step_int[i];
        }
    }
}

static int *get_nb_ressources(map_tile_t *tiles, int width, int height)
{
    static int nb_ressources[PLAYER] = {0, 0, 0, 0, 0, 0, 0};

    memset(nb_ressources, 0, sizeof(nb_ressources));
    for (int i = 0; i < width * height; i++) {
        nb_ressources[FOOD] += tiles[i].ressources[FOOD];
        nb_ressources[LINEMATE] += tiles[i].ressources[LINEMATE];
        nb_ressources[DERAUMERE] += tiles[i].ressources[DERAUMERE];
        nb_ressources[SIBUR] += tiles[i].ressources[SIBUR];
        nb_ressources[MENDIANE] += tiles[i].ressources[MENDIANE];
        nb_ressources[PHIRAS] += tiles[i].ressources[PHIRAS];
        nb_ressources[THYSTAME] += tiles[i].ressources[THYSTAME];
    }
    return nb_ressources;
}

void map_add_ressources(map_t *map)
{
    int nb_spawn_max[PLAYER] = {0};
    int nb_step_int[PLAYER] = {0};
    int nb_step[PLAYER] = {0};
    int *nb_ressources = NULL;

    if (map == NULL || map->tiles == NULL) {
        return;
    }
    nb_ressources = get_nb_ressources(map->tiles, map->width, map->height);
    for (int i = 0; i < PLAYER; i++) {
        nb_spawn_max[i] = (density[i] * map->width * map->height)
            - nb_ressources[i];
        nb_step_int[i] = map->width * map->height /
            ((nb_spawn_max[i] <= 0) ? 0.5 : nb_spawn_max[i]);
        nb_step[i] = nb_step_int[i];
    }
    for (int i = 0; i < map->width * map->height; i++) {
        add_ressources(map->tiles + i, nb_step_int, nb_step);
    }
}
