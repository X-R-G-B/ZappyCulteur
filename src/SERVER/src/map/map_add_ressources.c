/*
** EPITECH PROJECT, 2023
** zappy server map
** File description:
** add ressources
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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

static void add_ressources(map_tile_t *tiles, int nb_spawn_max[PLAYER],
    int size_tile)
{
    int index = 0;

    for (int i = 0; i < PLAYER; i++) {
        if (nb_spawn_max[i] <= 0) {
            continue;
        }
        index = rand() % size_tile;
        tiles[index].ressources[i] += 1;
        nb_spawn_max[i] -= 1;
    }
}

static void fill_map_add_ressources(map_t *map, int nb_spawn_max[PLAYER])
{
    int size_tile = map->height * map->width;

    while (nb_spawn_max[FOOD] > 0 || nb_spawn_max[LINEMATE] > 0 ||
            nb_spawn_max[DERAUMERE] > 0 || nb_spawn_max[SIBUR] > 0 ||
            nb_spawn_max[MENDIANE] > 0 || nb_spawn_max[PHIRAS] > 0 ||
            nb_spawn_max[THYSTAME] > 0) {
        for (int i = 0; i < size_tile; i++) {
            add_ressources(map->tiles, nb_spawn_max, size_tile);
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
    int *nb_ressources = NULL;

    if (map == NULL || map->tiles == NULL) {
        return;
    }
    nb_ressources = get_nb_ressources(map->tiles, map->width, map->height);
    for (int i = 0; i < PLAYER; i++) {
        nb_spawn_max[i] = (density[i] * map->width * map->height)
            - nb_ressources[i];
    }
    fill_map_add_ressources(map, nb_spawn_max);
}
