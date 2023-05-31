/*
** EPITECH PROJECT, 2023
** zappy server trantorien
** File description:
** reduce freq of action
*/

#include <stddef.h>
#include "ntw.h"
#include "zappy.h"
#include "trantorien.h"
#include "internal.h"

static void trantorien_need_update(trantorien_t *trantorien, zappy_t *zappy,
    ntw_client_t *cl, action_t *action)
{
    // TODO
}

static void move_up(action_t *actions[NB_PARALLEL_ACTION])
{
    for (int i = 1; i < NB_PARALLEL_ACTION; i++) {
        actions[i - 1] = actions[i];
    }
    actions[NB_PARALLEL_ACTION - 1] = NULL;
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
        move_up(trantorien->actions);
    }
}
