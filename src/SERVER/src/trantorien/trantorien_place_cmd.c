/*
** EPITECH PROJECT, 2023
** zappy server trantorien
** File description:
** place cmd action
*/

#include <stdbool.h>
#include <stddef.h>
#include "trantorien.h"
#include "internal.h"

bool trantorien_place_cmd(trantorien_t *trantorien, action_t *action)
{
    bool is_cmd_availible = false;

    if (trantorien == NULL) {
        return false;
    }
    for (int i = 0; i < NB_PARALLEL_ACTION; i++) {
        if (trantorien->actions[i] == NULL && i + 1 < NB_PARALLEL_ACTION) {
            trantorien->actions[i + 1] = NULL;
        }
        if (trantorien->actions[i] == NULL) {
            trantorien->actions[i] = action;
            is_cmd_availible = true;
            break;
        }
    }
    return is_cmd_availible;
}
