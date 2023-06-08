/*
** EPITECH PROJECT, 2023
** zappy server trantorien
** File description:
** action destroy
*/

#include <stddef.h>
#include <stdlib.h>
#include "trantorien.h"
#include "internal.h"

void action_destroy(action_t *action)
{
    if (action == NULL) {
        return;
    }
    if (action->code == BROADCAST) {
        free(action->param.broadcast_msg);
    }
    free(action);
}
