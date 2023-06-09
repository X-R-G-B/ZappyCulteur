/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** incantation_start
*/

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "circular_buffer.h"
#include "tlcllists.h"
#include "zappy.h"
#include "ntw.h"
#include "trantorien.h"
#include "client.h"

static void process_start_incant_trnt(ntw_client_t *cl, list_t *list_trnt,
    trantorien_t *trnt, trantorien_t *ref_trnt)
{
    circular_buffer_write(cl->write_to_outside, "Elevation underway\n");
    list_append(list_trnt, trnt, NULL, NULL);
    if (trnt == ref_trnt) {
        return;
    }
    trnt->incantation = ref_trnt->actions[0];
}

static void broadcast_incantation(trantorien_t *ref_trantorien, ntw_t *ntw,
    list_t *list_trnt)
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
            process_start_incant_trnt(ntw_cl, list_trnt, trantorien,
                ref_trantorien);
        }
    }
}

static void send_broadcast_graph(ntw_t *ntw, list_t *list_trnt,
    trantorien_t *ref_trnt)
{
    char tmp[10] = {0};
    char buff[1024] = {0};
    trantorien_t *trnt;

    snprintf(buff, 511, "pic %d %d %d", ref_trnt->x, ref_trnt->y,
        ref_trnt->level);
    for (L_EACH(x, list_trnt)) {
        trnt = L_DATA(x);
        if (trnt == NULL) {
            continue;
        }
        snprintf(tmp, 9, " %d", trnt->id);
        strcat(buff, tmp);
    }
    strcat(buff, "\n");
    broadcast_graphic(ntw, buff);
}

void broadcast_incantation_start(trantorien_t *ref_trantorien, zappy_t *zappy,
    ntw_client_t *cl)
{
    list_t *list_trnt = NULL;

    if (check_incantation_availability(
            ref_trantorien, zappy->map, zappy->ntw) == false) {
        circular_buffer_write(cl->write_to_outside, KO_RESPONSE);
        return;
    }
    list_trnt = list_create();
    if (list_trnt == NULL) {
        return;
    }
    broadcast_incantation(ref_trantorien, zappy->ntw, list_trnt);
    send_broadcast_graph(zappy->ntw, list_trnt, ref_trantorien);
}
