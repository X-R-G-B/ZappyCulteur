/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** command_look_around_utils
*/

#include "circular_buffer.h"
#include "ntw.h"
#include "trantorien.h"
#include "map.h"
#include <stdbool.h>

/*
 * direction NORTH(1)
  0   1   2   3   4   5   6   7   8   9
|---|---|---|---|---|---|---|---|---|---|
| 4 | 5 | 6 | 7 | 8 |   |   |   |   |   | 0
|---|---|---|---|---|---|---|---|---|---|
|   | 1 | 2 | 3 |   |   |   |   |   |   | 1
|---|---|---|---|---|---|---|---|---|---|
|   |   | R |   |   |   |   |   |   |   | 2
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 3
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 4
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 5
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 6
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 7
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 8
|---|---|---|---|---|---|---|---|---|---|
| 10| 11| 12| 13| 14| 15|   |   |   | 9 | 9
|---|---|---|---|---|---|---|---|---|---|

** T: trantorien
** S: SOUTH(3)
** E: EAST(2)
** W: WEST(4)
** N: NORTH(1)
  0   1   2   3   4   5   6   7   8   9
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 0
|---|---|---|---|---|---|---|---|---|---|
|   | N |   | E |   |   |   |   |   |   | 1
|---|---|---|---|---|---|---|---|---|---|
|   |   | T |   |   |   |   |   |   |   | 2
|---|---|---|---|---|---|---|---|---|---|
|   | W |   | S |   |   |   |   |   |   | 3
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 4
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 5
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 6
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 7
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 8
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 9
|---|---|---|---|---|---|---|---|---|---|
{x next from middle, y next from middle}
*/
static const int look_dir_reset[WEST][2] = {
    {-1, -1},
    {1, -1},
    {1, 1},
    {-1, 1},
};
static const int look_dir_next_tile[WEST][2] = {
    {1, 0},
    {0, 1},
    {-1, 0},
    {0, -1},
};

static const int index_ressource_ok[MAX_NB_RESOURCES] = {
    PLAYER,
    FOOD,
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME,
};
static const char *ressources_name[MAX_NB_RESOURCES] = {
    "food",
    "linemate",
    "deraumere",
    "sibur",
    "mendiane",
    "phiras",
    "thystame",
    "player"
};

static void send_single_tile(map_tile_t *tile, ntw_client_t *cl)
{
    int nb_ressources = 0;
    enum ressource_e r_idx;
    bool need_space = false;

    for (int i = 0; i < MAX_NB_RESOURCES; i++) {
        nb_ressources += tile->ressources[i];
    }
    if (nb_ressources > 1) {
        circular_buffer_write(cl->write_to_outside, " ");
    }
    for (int i = 0; i < nb_ressources; i++) {
        r_idx = index_ressource_ok[i];
        if (tile->ressources[r_idx] <= 0) {
            continue;
        }
        circular_buffer_write(cl->write_to_outside, (need_space) ? " " : "");
        circular_buffer_write(cl->write_to_outside, ressources_name[r_idx]);
        need_space = true;
    }
}

static void send_tiles_info(int cur_line_x_y[2], map_t *map, ntw_client_t *cl,
    const int pos[2])
{
    int map_i = 0;
    int nb_tile = (cur_line_x_y[0] * 2) + 1;
    int pos_x = pos[0];
    int pos_y = pos[1];
    enum direction_e dir = cur_line_x_y[1];

    for (int j = 0; j < nb_tile; j++) {
        if (j != 0) {
            circular_buffer_write(cl->write_to_outside, ",");
        }
        map_index_x_y_to_i(map,  pos_x, pos_y, &map_i);
        send_single_tile(&map->tiles[map_i], cl);
        pos_x += look_dir_next_tile[dir - NORTH][0];
        pos_y += look_dir_next_tile[dir - NORTH][1];
    }
}

void look_test(trantorien_t *tr, int lvl, map_t *map, ntw_client_t *cl)
{
    int pos[2] = {0, 0};
    int double_thing[2] = {0};
 
    double_thing[1] = tr->direction;
    circular_buffer_write(cl->write_to_outside, "[");
    for (int i = 0; i < lvl + 1; i++) {
        if (i != 0) {
            circular_buffer_write(cl->write_to_outside, ",");
        }
        pos[0] = tr->x + (look_dir_reset[tr->direction - NORTH][0] * i);
        pos[1] = tr->y + (look_dir_reset[tr->direction - NORTH][1] * i);
        double_thing[0] = i;
        send_tiles_info(double_thing, map, cl, pos);
    }
    circular_buffer_write(cl->write_to_outside, "]\n");
}

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
