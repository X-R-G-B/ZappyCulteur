/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** command_move
*/

#include <stddef.h>
#include <stdlib.h>
#include "ntw.h"
#include "zappy.h"
#include "command_reponses.h"

/**
** @brief table of displacement according to the direction [(x, y), ...]
** @note the first index is the direction - 1
**/
static const int direction_to_x[4][2] = {
    {0, -1},
    {1, 0},
    {0, 1},
    {-1, 0}
};

// TODO: function to remove trantorien from last pos from map tile
// TODO: and put it on the list of the new position tile

int command_move(trantorien_t *trantorien, zappy_t *zappy,
                        ntw_client_t *cl, action_t *action)
{
    int last[2] = {0, 0};

    if (trantorien == NULL || zappy == NULL || cl == NULL || action == NULL) {
        circular_buffer_write(cl->write_to_outside, KO_RESPONSE);
        return EXIT_FAILURE;
    }
    last[0] = trantorien->x;
    last[1] = trantorien->y;
    trantorien->x += direction_to_x[trantorien->direction - 1][0];
    trantorien->y += direction_to_x[trantorien->direction - 1][1];
    if (trantorien->x < 0)
        trantorien->x += zappy->map->width;
    if (trantorien->y < 0)
        trantorien->y += zappy->map->height;
    trantorien->x %= zappy->map->width;
    trantorien->y %= zappy->map->height;
    circular_buffer_write(cl->write_to_outside, OK_RESPONSE);
    return EXIT_SUCCESS;
}
