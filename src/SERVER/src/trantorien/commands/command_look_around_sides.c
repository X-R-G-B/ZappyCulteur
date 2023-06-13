/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** command_look_around_utils
*/

#include <stdbool.h>
#include "circular_buffer.h"
#include "ntw.h"
#include "trantorien.h"
#include "map.h"

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
    bool need_space = false;

    for (int i = 0; i < MAX_NB_RESOURCES; i++) {
        if (tile->ressources[i] <= 0) {
            continue;
        }
        circular_buffer_write(cl->write_to_outside, (need_space) ? " " : "");
        circular_buffer_write(cl->write_to_outside, ressources_name[i]);
        need_space = true;
    }
}

static int fix_pos(int pos, int size_max)
{
    while (pos < 0) {
        pos = size_max + pos;
    }
    return pos % size_max;
}

static void send_tiles_info(int cur_line_x_y[2], map_t *map, ntw_client_t *cl,
    const int pos[2])
{
    enum direction_e dir = cur_line_x_y[1];
    int nb_tile = (cur_line_x_y[0] * 2) + 1;
    int map_i = 0;
    int pos_x = 0;
    int pos_y = 0;

    for (int j = 0; j < nb_tile; j++) {
        pos_x = pos[0] + (look_dir_next_tile[dir - NORTH][0] * j);
        pos_x = fix_pos(pos_x, map->width);
        pos_y = pos[1] + (look_dir_next_tile[dir - NORTH][1] * j);
        pos_y = fix_pos(pos_y, map->height);
        if (j != 0) {
            circular_buffer_write(cl->write_to_outside, ",");
        }
        map_index_x_y_to_i(map,  pos_x, pos_y, &map_i);
        send_single_tile(&map->tiles[map_i], cl);
    }
}

void look_around(trantorien_t *tr, int lvl, map_t *map, ntw_client_t *cl)
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
        pos[0] = fix_pos(pos[0], map->width);
        pos[1] = tr->y + (look_dir_reset[tr->direction - NORTH][1] * i);
        pos[1] = fix_pos(pos[1], map->height);
        double_thing[0] = i;
        send_tiles_info(double_thing, map, cl, pos);
    }
    circular_buffer_write(cl->write_to_outside, "]\n");
}
