/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** command_take_object
*/

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "ntw.h"
#include "zappy.h"
#include "command_reponses.h"
#include "broadcast_events.h"

int command_take_object(trantorien_t *trantorien, zappy_t *zappy,
    ntw_client_t *cl, action_t *action)
{
    int i = 0;

    if (trantorien == NULL || zappy == NULL || cl == NULL || action == NULL) {
        return EXIT_FAILURE;
    }
    map_index_x_y_to_i(zappy->map, trantorien->x, trantorien->y, &i);
    if (action->param.object < PLAYER && action->param.object >= FOOD &&
            zappy->map->tiles[i].ressources[action->param.object] > 0) {
        zappy->map->tiles[i].ressources[action->param.object] -= 1;
        trantorien->ressources[action->param.object] += 1;
        circular_buffer_write(cl->write_to_outside, OK_RESPONSE);
        cmd_pgt(zappy->ntw, cl, action);
    } else {
        fprintf(stderr, "Take object %d (available: %d)\n",
            action->param.object,
            zappy->map->tiles[i].ressources[action->param.object]);
        circular_buffer_write(cl->write_to_outside, KO_RESPONSE);
    }
    return EXIT_SUCCESS;
}
