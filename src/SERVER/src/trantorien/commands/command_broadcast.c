/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** command_take_object
*/

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ntw.h"
#include "zappy.h"
#include "trantorien.h"
#include "map.h"

/*
|  -1  |  +0  |  +1  |
|------|------|------|------
|   0  |   1  |   2  |  -1
|------|------|------|------
|   7  |  xx  |   3  |  +0
|------|------|------|------
|   6  |   5  |   4  |  +1
|------|------|------|------
*/
static const int direction_to_follow[8][2] = {
    {-1, -1},
    {-1, 0},
    {-1, 1},
    {1, 0},
    {1, 1},
    {0, 1},
    {-1, 1},
    {-1, 0}
};

// TODO: Spread on the map and mark all case with list of trantorien = NULL
// TODO: Trantorien must have the circular buffer write in them to be hable
// TODO: to write to thier client
static void spread_broadcast(int x, int y, map_t *map, const char *msg)
{
    // if ()
}

static map_t *coppy_map(map_t *map)
{
    map_t *new = NULL;

    new = malloc(sizeof(map_t));
    if (new == NULL) {
        return NULL;
    }
    new->width = map->width;
    new->height = map->height;
    new->tiles = malloc(sizeof(map_tile_t) * (map->width * map->height));
    memcpy(new->tiles, map->tiles,
        sizeof(map_tile_t) * (map->width * map->height));
    return new;
}

int command_broadcast(trantorien_t *trantorien, zappy_t *zappy,
    ntw_client_t *cl, action_t *action)
{
    if (trantorien == NULL || zappy == NULL || cl == NULL || action == NULL) {
        return EXIT_FAILURE;
    }
    spread_broadcast(trantorien->x, trantorien->y, zappy,
        action->param.broadcast_msg);
    return EXIT_SUCCESS;
}
