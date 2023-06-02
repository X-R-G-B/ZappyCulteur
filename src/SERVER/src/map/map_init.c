/*
** EPITECH PROJECT, 2023
** zappy server map
** File description:
** init
*/

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "map.h"
#include "tlcllists.h"

static bool map_tiles_init(int width, int height, map_tile_t *tiles)
{
    for (int i = 0; i < width * height; i++) {
        tiles[i].trantors = list_create();
        if (tiles[i].trantors == NULL) {
            return false;
        }
    }
    return true;
}

map_t *map_init(int width, int height)
{
    map_t *map = NULL;

    map = malloc(sizeof(map_t));
    if (map == NULL) {
        return NULL;
    }
    map->height = height;
    map->width = width;
    map->tiles = malloc(sizeof(map_tile_t) * (width * height));
    if (map->tiles == NULL) {
        map_destroy(map);
        return NULL;
    }
    memset(map->tiles, 0, sizeof(map_tile_t) * (width * height));
    if (map_tiles_init(width, height, map->tiles) == false) {
        map_destroy(map);
        return NULL;
    }
    map_add_ressources(map);
    return map;
}
