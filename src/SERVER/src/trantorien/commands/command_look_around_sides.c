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

// north
void look_north_tiles_ressources(trantorien_t *trantorien, int lvl, map_t *map,
    ntw_client_t *cl)
{
    int tile[2] = {0, 0};
    int map_i = 0;
    int nb_turns = 0;

    tile[0] = get_min_case_sub(trantorien->x, lvl, map->width);
    tile[1] = get_min_case_sub(trantorien->y, lvl, map->height);
    nb_turns = 1 + (lvl * 2);
    for (int turn = 0; turn < nb_turns;
            tile[0] = (tile[0] + 1) % map->width, turn++) {
        map_index_x_y_to_i(map,  tile[0], tile[1], &map_i);
        if (lvl == 0 && turn == 0)
            send_tile_ressources(cl, &map->tiles[map_i], -1);
        if (lvl == trantorien->level && turn == nb_turns - 1)
            send_tile_ressources(cl, &map->tiles[map_i], 1);
        if ((lvl != 0 || turn != 0) && (lvl != trantorien->level
                || turn != nb_turns)) {
            send_tile_ressources(cl, &map->tiles[map_i], 0);
        }
    }
}

// east
void look_east_tiles_ressources(trantorien_t *trantorien, int lvl, map_t *map,
    ntw_client_t *cl)
{
    int tile[2] = {0, 0};
    int map_i = 0;
    int nb_turns = 0;

    tile[0] = get_min_case_add(trantorien->x, lvl, map->width);
    tile[1] = get_min_case_sub(trantorien->y, lvl, map->height);
    nb_turns = 1 + (lvl * 2);
    for (int turn = 0; turn < nb_turns;
            tile[1] = (tile[1] + 1) % map->height, turn++) {
        map_index_x_y_to_i(map, tile[0], tile[1], &map_i);
        if (lvl == 0 && turn == 0)
            send_tile_ressources(cl, &map->tiles[map_i], -1);
        if (lvl == trantorien->level && turn == nb_turns - 1)
            send_tile_ressources(cl, &map->tiles[map_i], 1);
        if ((lvl != 0 || turn != 0) && (lvl != trantorien->level
                || turn != nb_turns)) {
            send_tile_ressources(cl, &map->tiles[map_i], 0);
        }
    }
}

// south
void look_south_tiles_ressources(trantorien_t *trantorien, int lvl, map_t *map,
    ntw_client_t *cl)
{
    int tile[2] = {0, 0};
    int map_i = 0;
    int nb_turns = 0;

    tile[0] = get_min_case_add(trantorien->x, lvl, map->width);
    tile[1] = get_min_case_add(trantorien->y, lvl, map->height);
    nb_turns = 1 + (lvl * 2);
    for (int turn = 0; turn < nb_turns; tile[0] = (tile[0] - 1 < 0) ?
            map->width - 1 : tile[0] - 1, turn++) {
        map_index_x_y_to_i(map, tile[0], tile[1], &map_i);
        if (lvl == 0 && turn == 0)
            send_tile_ressources(cl, &map->tiles[map_i], -1);
        if (lvl == trantorien->level && turn == nb_turns - 1)
            send_tile_ressources(cl, &map->tiles[map_i], 1);
        if ((lvl != 0 || turn != 0) && (lvl != trantorien->level
                || turn != nb_turns)) {
            send_tile_ressources(cl, &map->tiles[map_i], 0);
        }
    }
}

// west
void look_west_tiles_ressources(trantorien_t *trantorien, int lvl, map_t *map,
    ntw_client_t *cl)
{
    int tile[2] = {0, 0};
    int map_i = 0;
    int nb_turns = 0;

    tile[0] = get_min_case_sub(trantorien->x, lvl, map->width);
    tile[1] = get_min_case_sub(trantorien->y, lvl, map->height);
    nb_turns = 1 + (lvl * 2);
    for (int turn = 0; turn < nb_turns; tile[1] = (tile[1] - 1 < 0) ?
            map->width - 1 : tile[1] - 1, turn++) {
        map_index_x_y_to_i(map, tile[0], tile[1], &map_i);
        if (lvl == 0 && turn == 0)
            send_tile_ressources(cl, &map->tiles[map_i], -1);
        if (lvl == trantorien->level && turn == nb_turns - 1)
            send_tile_ressources(cl, &map->tiles[map_i], 1);
        if ((lvl != 0 || turn != 0) && (lvl != trantorien->level
                || turn != nb_turns)) {
            send_tile_ressources(cl, &map->tiles[map_i], 0);
        }
    }
}
