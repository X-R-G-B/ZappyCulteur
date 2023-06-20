/*
** EPITECH PROJECT, 2023
** zappy server graphic cmd
** File description:
** mct
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "circular_buffer.h"
#include "ntw.h"
#include "map.h"
#include "internal.h"
#include "tlcstrings.h"

static bool send_pos(ntw_client_t *cl, int x, int y)
{
    char buff[512] = {0};

    snprintf(buff, 511, "%d %d", x, y);
    circular_buffer_write(cl->write_to_outside, buff);
    return true;
}

static bool send_ressources(map_tile_t *tile, ntw_client_t *cl)
{
    char buff[1024] = {0};

    snprintf(buff, 1023, "%d %d %d %d %d %d %d",
        tile->ressources[FOOD],
        tile->ressources[LINEMATE],
        tile->ressources[DERAUMERE],
        tile->ressources[SIBUR],
        tile->ressources[MENDIANE],
        tile->ressources[PHIRAS],
        tile->ressources[THYSTAME]
    );
    circular_buffer_write(cl->write_to_outside, buff);
    return true;
}

bool cmd_bct_x_y(zappy_t *zappy, ntw_client_t *cl, int x, int y)
{
    int i;

    if (x >= zappy->map->width || y >= zappy->map->height) {
        return false;
    }
    circular_buffer_write(cl->write_to_outside, "bct ");
    send_pos(cl, x, y);
    circular_buffer_write(cl->write_to_outside, " ");
    map_index_x_y_to_i(zappy->map, x, y, &i);
    send_ressources(zappy->map->tiles + i, cl);
    circular_buffer_write(cl->write_to_outside, "\n");
    return true;
}

bool cmd_bct(zappy_t *zappy, ntw_client_t *cl, char **cmd_split)
{
    int x;
    int y;
    bool status = true;

    if (zappy == NULL || cmd_split[1] == NULL || cmd_split[2] == NULL ||
            strlen(cmd_split[1]) == 0 || strlen(cmd_split[2]) == 0 ||
            x_strcontainc("0123456789", cmd_split[1][0]) == 0 ||
            x_strcontainc("0123456789", cmd_split[2][0]) == 0) {
        return false;
    }
    if (cmd_split[2][strlen(cmd_split[2]) - 1] == '\n') {
        cmd_split[2][strlen(cmd_split[2]) - 1] = '\0';
    }
    x = atoi(cmd_split[1]);
    y = atoi(cmd_split[2]);
    status = cmd_bct_x_y(zappy, cl, x, y);
    return status;
}
