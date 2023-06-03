/*
** EPITECH PROJECT, 2023
** zappy server trantorien
** File description:
** reduce freq of action
*/

#include <stddef.h>
#include <stdio.h>
#include "circular_buffer.h"
#include "ntw.h"
#include "zappy.h"
#include "trantorien.h"
#include "internal.h"
#include "client.h"

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
    command_incantation,
};

static void trantorien_need_update(trantorien_t *trantorien, zappy_t *zappy,
    ntw_client_t *cl, action_t *action)
{
    if (trantorien_commands[action->code] == NULL) {
        circular_buffer_write(cl->write_to_outside, "ko\n");
        printf("%s%d\n", "Command not handled: ", action->code);
        return;
    }
    trantorien_commands[action->code](trantorien, zappy, cl, action);
}

static void move_up(action_t *actions[NB_PARALLEL_ACTION],
    trantorien_t *trantorien, zappy_t *zappy, ntw_client_t *cl)
{
    for (int i = 1; i < NB_PARALLEL_ACTION; i++) {
        actions[i - 1] = actions[i];
    }
    actions[NB_PARALLEL_ACTION - 1] = NULL;
    if (actions[0]->code == INCANTATION) {
        broadcast_incantation_start(trantorien, zappy, cl);
    }
}

void trantorien_reduce_freq(trantorien_t *trantorien, zappy_t *zappy,
    ntw_client_t *cl)
{
    if (trantorien == NULL) {
        return;
    }
    if (trantorien->actions[0] == NULL && trantorien->actions[1] == NULL) {
        return;
    }
    if (trantorien->incantation != NULL) {
        return;
    }
    if (trantorien->actions[0] == NULL) {
        move_up(trantorien->actions, trantorien, zappy, cl);
    }
    trantorien->actions[0]->freq--;
    if (trantorien->actions[0]->freq == 0) {
        trantorien_need_update(trantorien, zappy, cl, trantorien->actions[0]);
        action_destroy(trantorien->actions[0]);
        trantorien->actions[0] = NULL;
        move_up(trantorien->actions, trantorien, zappy, cl);
    }
}
