/*
** EPITECH PROJECT, 2023
** zappy server trantorien
** File description:
** reduce freq of action
*/

#include <stddef.h>
#include <stdio.h>
#include "ntw.h"
#include "zappy.h"
#include "trantorien.h"
#include "internal.h"
#include "client.h"

static void trantorien_need_update(trantorien_t *trantorien, zappy_t *zappy,
    ntw_client_t *cl, action_t *action)
{
    static int (*trantorien_commands[MAX_CMD_CODE])(trantorien_t *, zappy_t *,
        ntw_client_t *, action_t *) = {
        command_move,
        command_turn_right,
        command_turn_left,
        command_look_around,
        command_inventory,
        NULL,
        NULL,
        NULL,
        command_take_object,
        command_set_object_down,
        command_start_incantation,
    };

    if (trantorien_commands[action->code] == NULL)
        return;
    trantorien_commands[action->code](trantorien, zappy, cl, action);
}

static void broadcast_incantation(trantorien_t *ref_trantorien, ntw_t *ntw)
{
    char buff[512] = {0};
    int trantorien_lvl = ref_trantorien->level;
    client_t *cl = NULL;
    ntw_client_t *ntw_cl = NULL;
    trantorien_t *trantorien = NULL;

    for (L_EACH(client, ntw->clients)) {
        ntw_cl = L_DATA(client);
        cl = L_DATA(ntw_cl);
        if (cl == NULL || cl->type != AI)
            continue;
        trantorien = cl->cl.ai.trantorien;
        if (trantorien != NULL && trantorien->level == trantorien_lvl
                && ref_trantorien->x == trantorien->x
                && ref_trantorien->y == trantorien->y) {
            snprintf(buff, 511, "Elevation underway Current level: %d\n",
                trantorien_lvl);
            circular_buffer_write(ntw_cl->write_to_outside, buff);
        }
    }
}

static void move_up(action_t *actions[NB_PARALLEL_ACTION],
    trantorien_t *trantorien, ntw_t *ntw)
{
    for (int i = 1; i < NB_PARALLEL_ACTION; i++) {
        actions[i - 1] = actions[i];
    }
    actions[NB_PARALLEL_ACTION - 1] = NULL;
    if (actions[0]->code == INCANTATION) {
        broadcast_incantation(trantorien, ntw);
    }
}

void trantorien_reduce_freq(trantorien_t *trantorien, zappy_t *zappy,
    ntw_client_t *cl)
{
    if (trantorien == NULL) {
        return;
    }
    if (trantorien->actions[0] == NULL) {
        return;
    }
    trantorien->actions[0]->freq--;
    if (trantorien->actions[0]->freq == 0) {
        trantorien_need_update(trantorien, zappy, cl, trantorien->actions[0]);
        action_destroy(trantorien->actions[0]);
        trantorien->actions[0] = NULL;
        move_up(trantorien->actions, trantorien, zappy->ntw);
    }
}
