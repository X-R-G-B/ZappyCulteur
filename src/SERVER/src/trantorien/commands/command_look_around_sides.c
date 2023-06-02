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
    int min_case[2] = {0, 0};
    int last_lvl_case = 0;
    int map_i = 0;

    min_case[0] = get_min_case_sub(trantorien->x, lvl, map->width);
    min_case[1] = get_min_case_sub(trantorien->y, lvl, map->height);
    last_lvl_case = (trantorien->x + lvl) % map->width;
    last_lvl_case = (last_lvl_case < 0) ?
        last_lvl_case + map->width : last_lvl_case;
    for (int x = min_case[0]; x <= last_lvl_case; x = (x + 1) % map->width) {
        map_index_x_y_to_i(map, x, min_case[1], &map_i);
        if (lvl == 0 && x == min_case[0])
            send_tile_ressources(cl, map[map_i].tiles, -1);
        if (lvl == trantorien->level && x == last_lvl_case)
            send_tile_ressources(cl, map[map_i].tiles, 1);
        if (lvl != 0 && x != min_case[0] && lvl != trantorien->level
                && x != last_lvl_case) {
            send_tile_ressources(cl, map[map_i].tiles, 0);
        }
    }
}

// east
void look_east_tiles_ressources(trantorien_t *trantorien, int lvl, map_t *map,
    ntw_client_t *cl)
{
    int min_case[2] = {0, 0};
    int last_lvl_case = 0;
    int map_i = 0;

    min_case[0] = get_min_case_add(trantorien->x, lvl, map->width);
    min_case[1] = get_min_case_sub(trantorien->y, lvl, map->height);
    last_lvl_case = (trantorien->y + lvl) % map->width;
    last_lvl_case = (last_lvl_case < 0) ?
        last_lvl_case + map->height : last_lvl_case;
    for (int y = min_case[1]; y <= last_lvl_case; y = (y + 1) % map->height) {
        map_index_x_y_to_i(map, min_case[0], y, &map_i);
        if (lvl == 0 && y == min_case[1])
            send_tile_ressources(cl, map[map_i].tiles, -1);
        if (lvl == trantorien->level && y == last_lvl_case)
            send_tile_ressources(cl, map[map_i].tiles, 1);
        if (lvl != 0 && y != min_case[1] && lvl != trantorien->level
                && y != last_lvl_case) {
            send_tile_ressources(cl, map[map_i].tiles, 0);
        }
    }
}

// south
void look_south_tiles_ressources(trantorien_t *trantorien, int lvl, map_t *map,
    ntw_client_t *cl)
{
    int min_case[2] = {0, 0};
    int last_lvl_case = 0;
    int map_i = 0;

    min_case[0] = get_min_case_add(trantorien->x, lvl, map->width);
    min_case[1] = get_min_case_add(trantorien->y, lvl, map->height);
    last_lvl_case = (trantorien->x - lvl) % map->width;
    last_lvl_case = (last_lvl_case < 0) ?
        last_lvl_case + map->width : last_lvl_case;
    for (int x = min_case[0]; x <= last_lvl_case;
            x = (x - 1 < 0) ? map->width - 1 : x - 1) {
        map_index_x_y_to_i(map, x, min_case[1], &map_i);
        if (lvl == 0 && x == min_case[0])
            send_tile_ressources(cl, map[map_i].tiles, -1);
        if (lvl == trantorien->level && x == last_lvl_case)
            send_tile_ressources(cl, map[map_i].tiles, 1);
        if (lvl != 0 && x != min_case[0] && lvl != trantorien->level
                && x != last_lvl_case)
            send_tile_ressources(cl, map[map_i].tiles, 0);
    }
}

// west
void look_west_tiles_ressources(trantorien_t *trantorien, int lvl, map_t *map,
    ntw_client_t *cl)
{
    int min_case[2] = {0, 0};
    int last_lvl_case = 0;
    int map_i = 0;

    min_case[0] = get_min_case_sub(trantorien->x, lvl, map->width);
    min_case[1] = get_min_case_sub(trantorien->y, lvl, map->height);
    last_lvl_case = (trantorien->y + lvl) % map->width;
    last_lvl_case = (last_lvl_case < 0) ?
        last_lvl_case + map->height : last_lvl_case;
    for (int y = min_case[1]; y <= last_lvl_case;
            y = (y - 1 < 0) ? map->width - 1 : y - 1) {
        map_index_x_y_to_i(map, min_case[0], y, &map_i);
        if (lvl == 0 && y == min_case[1])
            send_tile_ressources(cl, map[map_i].tiles, -1);
        if (lvl == trantorien->level && y == last_lvl_case)
            send_tile_ressources(cl, map[map_i].tiles, 1);
        if (lvl != 0 && y != min_case[1] && lvl != trantorien->level
                && y != last_lvl_case)
            send_tile_ressources(cl, map[map_i].tiles, 0);
    }
}
