/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** set_object_down
*/

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "ntw.h"
#include "zappy.h"
#include "trantorien.h"
#include "map.h"

static void send_broadcast(enum ressource_e obj, ntw_t *ntw, int player_id)
{
    char buff[512] = {0};

    snprintf(buff, 511, "pdr %d %d\n", player_id, obj);
    broadcast_graphic(ntw, buff);
}

int command_set_object_down(trantorien_t *trantorien, zappy_t *zappy,
                        ntw_client_t *cl, action_t *action)
{
    int i = 0;

    if (trantorien == NULL || zappy == NULL || cl == NULL || action == NULL)
        return EXIT_FAILURE;
    if (trantorien->ressources[action->param.object] > 0 &&
            action->param.object < PLAYER) {
        trantorien->ressources[action->param.object] -= 1;
        map_index_x_y_to_i(zappy->map, trantorien->x, trantorien->y, &i);
        zappy->map[i].tiles->ressources[action->param.object] += 1;
        circular_buffer_write(cl->write_to_outside, "ok\n");
        send_broadcast(action->param.object, zappy->ntw, trantorien->id);
    } else {
        circular_buffer_write(cl->write_to_outside, KO_RESPONSE);
    }
    return EXIT_SUCCESS;
}
