/*
** EPITECH PROJECT, 2023
** zappy server graphic cmd
** File description:
** mct
*/

#include <stdbool.h>
#include "ntw.h"
#include "map.h"
#include "internal.h"
#include "zappy.h"

bool cmd_mct(zappy_t *zappy, ntw_client_t *cl,
    __attribute__((unused)) char **cmd_split)
{
    int x;
    int y;
    bool status = true;

    for (int i = 0; i < zappy->map->width * zappy->map->height &&
            status == true; i++) {
        map_index_i_to_x_y(zappy->map, i, &x, &y);
        status = cmd_bct_x_y(zappy, cl, x, y);
    }
    return status;
}
