/*
** EPITECH PROJECT, 2023
** zappy server map
** File description:
** add ressources
*/

#include <string.h>
#include <stdio.h>
#include "map.h"

static float density[MAX_NB_RESOURCES] = {
    0.5,
    0.3,
    0.15,
    0.1,
    0.1,
    0.08,
    0.05,
    0.00,
    0.00,
};

static void add_ressources(map_tile_t *tile,
    int const nb_step_int[MAX_NB_RESOURCES],
    int nb_step[MAX_NB_RESOURCES])
{
    for (int i = 0; i < MAX_NB_RESOURCES; i++) {
        nb_step[i] -= 1;
        if (nb_step[i] <= 0) {
            tile->ressources[i] += 1;
            nb_step[i] = nb_step_int[i];
        }
    }
}

static void check_ressources(map_tile_t *tiles, int width, int height,
    int const nb_spawn_max[MAX_NB_RESOURCES])
{
    int nb_ressources[MAX_NB_RESOURCES] = {0, 0, 0, 0, 0, 0, 0};

    for (int i = 0; i < width * height; i++) {
        nb_ressources[FOOD] += tiles[i].ressources[FOOD];
        nb_ressources[LINEMATE] += tiles[i].ressources[LINEMATE];
        nb_ressources[DERAUMERE] += tiles[i].ressources[DERAUMERE];
        nb_ressources[SIBUR] += tiles[i].ressources[SIBUR];
        nb_ressources[MENDIANE] += tiles[i].ressources[MENDIANE];
        nb_ressources[PHIRAS] += tiles[i].ressources[PHIRAS];
        nb_ressources[THYSTAME] += tiles[i].ressources[THYSTAME];
    }
    for (int i = 0; i < MAX_NB_RESOURCES; i++) {
        if (nb_ressources[i] != nb_spawn_max[i]) {
            fprintf(stderr, "%s :: %s:%d :: %s:%d\n",
                "WARN: ressources didn't match",
                "ressources on map", nb_ressources[i],
                "ressources expected", nb_spawn_max[i]);
        }
    }
}

void map_add_ressources(map_t *map)
{
    int nb_spawn_max[MAX_NB_RESOURCES] = {0};
    int nb_step_int[MAX_NB_RESOURCES] = {0};
    int nb_step[MAX_NB_RESOURCES] = {0};

    if (map == NULL || map->tiles == NULL) {
        return;
    }
    for (int i = 0; i < MAX_NB_RESOURCES; i++) {
        nb_spawn_max[i] = density[i] * map->width * map->height;
        printf("INFO: nb_spawn_max[%d] = %d\n", i, nb_spawn_max[i]);
        nb_step_int[i] = (nb_spawn_max[i] == 0) ?
            0 : map->width * map->height / nb_spawn_max[i];
        printf("INFO: nb_step_int[%d] = %d\n", i, nb_step_int[i]);
        nb_step[i] = nb_step_int[i];
    }
    for (int i = 0; i < map->width * map->height; i++) {
        add_ressources(map->tiles + i, nb_step_int, nb_step);
    }
    check_ressources(map->tiles, map->width, map->height, nb_spawn_max);
}
