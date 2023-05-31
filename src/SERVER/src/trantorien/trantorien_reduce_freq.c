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

void trantorien_reduce_freq(trantorien_t *trantorien, zappy_t *zappy,
    ntw_client_t *cl)
{
    if (trantorien == NULL) {
        return;
    }
    for (int i = 0; i < NB_PARALLEL_ACTION; i++) {
        if (trantorien->actions[i] == NULL) {
            continue;
        }
        trantorien->actions[i]->freq--;
        if (trantorien->actions[i]->freq == 0) {
            trantorien_need_update(trantorien, zappy, cl,
                trantorien->actions[i]);
            action_destroy(trantorien->actions[i]);
            trantorien->actions[i] = NULL;
        }
    }
}
