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
#include "llog.h"
#include "zappy.h"
#include "command_reponses.h"
#include "broadcast_events.h"

static const char *format_err = "Set object %d (available: %d)\n";

int command_set_object_down(trantorien_t *trantorien, zappy_t *zappy,
    ntw_client_t *cl, action_t *action)
{
    int i = 0;

    if (trantorien == NULL || zappy == NULL || cl == NULL || action == NULL) {
        return EXIT_FAILURE;
    }
    if (action->param.object < PLAYER && action->param.object >= FOOD &&
            trantorien->ressources[action->param.object] > 0) {
        trantorien->ressources[action->param.object] -= 1;
        map_index_x_y_to_i(zappy->map, trantorien->x, trantorien->y, &i);
        zappy->map->tiles[i].ressources[action->param.object] += 1;
        circular_buffer_write(cl->write_to_outside, OK_RESPONSE);
        cmd_pdr(zappy->ntw, cl, action);
    } else {
        llog_write_f(LOG_FILE_AIC, LLOG_WARNING, format_err,
            action->param.object,
            trantorien->ressources[action->param.object]);
        circular_buffer_write(cl->write_to_outside, KO_RESPONSE);
    }
    return EXIT_SUCCESS;
}
