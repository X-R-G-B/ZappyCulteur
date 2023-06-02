/*
** EPITECH PROJECT, 2023
** zappy server map
** File description:
** destroy
*/

#include <stdlib.h>
#include "tlcllists.h"
#include "map.h"

void map_destroy(map_t *map)
{
    if (map == NULL) {
        return;
    }
    if (map->tiles != NULL) {
        for (int i = 0; i < map->width * map->height; i++) {
            list_delete(map->tiles[i].trantors);
        }
    }
    free(map->tiles);
    free(map);
}
