/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** command_eject
*/

#include <stddef.h>
#include <stdlib.h>
#include "llog.h"
#include "ntw.h"
#include "zappy.h"
#include "client.h"
#include "command_reponses.h"
#include "broadcast_events.h"

static void remove_eggs_on_tile(trantorien_t *tr_src,
    list_t *trantoriens_available)
{
    trantorien_t *tr = NULL;
    list_t *to_remove = list_create();

    for (L_EACH(trantorien, trantoriens_available)) {
        tr = L_DATA(trantorien);
        if (tr == NULL) {
            continue;
        }
        if (IS_SAME_TR_POS(tr_src, tr)) {
            list_append(to_remove, trantorien, NULL, NULL);
        }
    }
    llog_write_f(LOG_FILE_AIC, LLOG_INFO, "removed %d eggs on tile x:%d y:%d",
        to_remove->len, tr_src->x, tr_src->y);
    for (L_EACH(trantorien, to_remove)) {
        list_remove_ptrnode(trantoriens_available, trantorien->data);
    }
    list_delete(to_remove);
}

static void apply_eject_tr_pos(trantorien_t *trantorien,
    enum direction_e dir, map_t *map)
{
    switch (dir) {
        case NORTH:
            trantorien->y -= 1;
            trantorien->y += (trantorien->y < 0) ? map->height : 0;
            break;
        case SOUTH:
            trantorien->y += 1;
            trantorien->y %= map->height;
            break;
        case EAST:
            trantorien->x += 1;
            trantorien->x %= map->width;
            break;
        case WEST:
            trantorien->x -= 1;
            trantorien->x += (trantorien->x < 0) ? map->width : 0;
            break;
        default:
            break;
    }
}

static void send_eject_broadcast(ntw_t *ntw, ntw_client_t *cl,
    trantorien_t *tr)
{
    if (cl == NULL || tr == NULL) {
        return;
    }
    if (tr->actions[0] != NULL) {
        action_destroy(tr->actions[0]);
        tr->actions[0] = NULL;
        circular_buffer_write(cl->write_to_outside, KO_EJECT_RESPONSE);
    }
    cmd_pex(ntw, cl, tr);
    circular_buffer_write(cl->write_to_outside, EJECT_RESPONSE);
}

int command_eject(trantorien_t *trantorien_src, zappy_t *zappy,
ntw_client_t *cl_src, action_t *action)
{
    client_t *cl = NULL;
    trantorien_t *tr = NULL;

    if (IS_CMD_ARG_NL(trantorien_src, zappy, cl_src, action)) {
        circular_buffer_write(cl_src->write_to_outside, KO_RESPONSE);
        return EXIT_FAILURE;
    }
    for (L_EACH(client, zappy->ntw->clients)) {
        cl = L_DATA(L_DATAT(ntw_client_t *, client));
        if (cl == NULL || cl->type != AI || cl->cl.ai.trantorien == NULL)
            continue;
        tr = cl->cl.ai.trantorien;
        if (!(IS_SAME_TR_POS(trantorien_src, tr)) || tr == trantorien_src)
            continue;
        apply_eject_tr_pos(tr, trantorien_src->direction, zappy->map);
        send_eject_broadcast(zappy->ntw, L_DATA(client), tr);
    }
    circular_buffer_write(cl_src->write_to_outside, OK_RESPONSE);
    remove_eggs_on_tile(trantorien_src, zappy->trantoriens_available);
    return EXIT_SUCCESS;
}
