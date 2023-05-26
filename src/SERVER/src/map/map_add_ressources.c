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
};

static void set_ressources(map_tile_t *tile, int modifs[MAX_NB_RESOURCES])
{
    tile->nb_food = modifs[FOOD];
    tile->nb_linemate = modifs[LINEMATE];
    tile->nb_deraumere = modifs[DERAUMERE];
    tile->nb_sibur = modifs[SIBUR];
    tile->nb_mendiane = modifs[MENDIANE];
    tile->nb_phiras = modifs[PHIRAS];
    tile->nb_thystame = modifs[THYSTAME];
}

static void add_ressources(map_tile_t *tile,
    int const nb_step_int[MAX_NB_RESOURCES],
    int nb_step[MAX_NB_RESOURCES])
{
    int modifs[MAX_NB_RESOURCES] = {
        tile->nb_food,
        tile->nb_linemate,
        tile->nb_deraumere,
        tile->nb_sibur,
        tile->nb_mendiane,
        tile->nb_phiras,
        tile->nb_thystame
    };

    for (int i = 0; i < MAX_NB_RESOURCES; i++) {
        nb_step[i] -= 1;
        if (nb_step[i] <= 0) {
            modifs[i] += 1;
            nb_step[i] = nb_step_int[i];
        }
    }
    set_ressources(tile, modifs);
}

static void check_ressources(map_tile_t *tiles, int width, int height,
    int const nb_spawn_max[MAX_NB_RESOURCES])
{
    int nb_ressources[MAX_NB_RESOURCES] = {0, 0, 0, 0, 0, 0, 0};

    for (int i = 0; i < width * height; i++) {
        nb_ressources[0] += tiles[i].nb_food;
        nb_ressources[1] += tiles[i].nb_linemate;
        nb_ressources[2] += tiles[i].nb_deraumere;
        nb_ressources[3] += tiles[i].nb_sibur;
        nb_ressources[4] += tiles[i].nb_mendiane;
        nb_ressources[5] += tiles[i].nb_phiras;
        nb_ressources[6] += tiles[i].nb_thystame;
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
    int nb_spawn_max[MAX_NB_RESOURCES] = {0, 0, 0, 0, 0, 0, 0};
    int nb_step_int[MAX_NB_RESOURCES] = {0, 0, 0, 0, 0, 0, 0};
    int nb_step[MAX_NB_RESOURCES] = {0, 0, 0, 0, 0, 0, 0};

    for (int i = 0; i < MAX_NB_RESOURCES; i++) {
        nb_spawn_max[i] = density[i] * map->width * map->height;
        printf("INFO: nb_spawn_max[%d] = %d\n", i, nb_spawn_max[i]);
        nb_step_int[i] = map->width * map->height / nb_spawn_max[i];
        printf("INFO: nb_step_int[%d] = %d\n", i, nb_step_int[i]);
        nb_step[i] = nb_step_int[i];
    }
    for (int i = 0; i < map->width * map->height; i++) {
        add_ressources(map->tiles + i, nb_step_int, nb_step);
    }
    check_ressources(map->tiles, map->width, map->height, nb_spawn_max);
}
