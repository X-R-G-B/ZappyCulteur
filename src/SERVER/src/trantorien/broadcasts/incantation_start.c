/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** incantation_start
*/

#include <stdbool.h>
#include <stdio.h>
#include "circular_buffer.h"
#include "zappy.h"
#include "ntw.h"
#include "trantorien.h"
#include "client.h"

static void send_msg(int trantorien_lvl, ntw_client_t *cl)
{
    char buff[512] = {0};

    snprintf(buff, 511, "Elevation underway Current level: %d\n",
        trantorien_lvl);
    circular_buffer_write(cl->write_to_outside, buff);
}

static void broadcast_incantation(trantorien_t *ref_trantorien, ntw_t *ntw)
{
    int trantorien_lvl = ref_trantorien->level;
    client_t *cl = NULL;
    ntw_client_t *ntw_cl = NULL;
    trantorien_t *trantorien = NULL;

    for (L_EACH(client, ntw->clients)) {
        ntw_cl = L_DATA(client);
        cl = L_DATA(ntw_cl);
        if (cl == NULL || cl->type != AI) {
            continue;
        }
        trantorien = cl->cl.ai.trantorien;
        if (trantorien != NULL && trantorien->level == trantorien_lvl
                && ref_trantorien->x == trantorien->x
                && ref_trantorien->y == trantorien->y) {
            send_msg(trantorien_lvl, ntw_cl);
            trantorien->incantation = ref_trantorien->actions[0];
        }
    }
}

void broadcast_incantation_start(trantorien_t *ref_trantorien, zappy_t *zappy,
    ntw_client_t *cl)
{
    if (check_incantation_availability(
            ref_trantorien, zappy->map, zappy->ntw) == false) {
        circular_buffer_write(cl->write_to_outside, "ko\n");
        return;
    }
    broadcast_incantation(ref_trantorien, zappy->ntw);
}
