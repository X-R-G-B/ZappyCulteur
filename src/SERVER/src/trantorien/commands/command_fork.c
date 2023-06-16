/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** command_fork
*/

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "ntw.h"
#include "client.h"
#include "zappy.h"
#include "command_reponses.h"
#include "broadcast_events.h"

int command_fork(trantorien_t *trantorien, zappy_t *zappy,
ntw_client_t *cl, action_t *action)
{
    trantorien_t *new_trantorien = NULL;

    if (trantorien == NULL || zappy == NULL || cl == NULL || action == NULL) {
        circular_buffer_write(cl->write_to_outside, KO_RESPONSE);
        return EXIT_FAILURE;
    }
    new_trantorien = trantorien_init(trantorien->team_name,
        zappy->map->width, zappy->map->height);
    new_trantorien->x = trantorien->x;
    new_trantorien->y = trantorien->y;
    if (!new_trantorien ||
        list_append(zappy->trantoriens_available, new_trantorien,
        (void (*)(void *)) &trantorien_destroy, NULL) == NULL) {
        circular_buffer_write(cl->write_to_outside, KO_RESPONSE);
        return EXIT_FAILURE;
    }
    circular_buffer_write(cl->write_to_outside, OK_RESPONSE);
    cmd_enw(zappy->ntw, cl);
    return EXIT_FAILURE;
}
