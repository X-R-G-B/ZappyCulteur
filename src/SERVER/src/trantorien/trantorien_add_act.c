/*
** EPITECH PROJECT, 2023
** zappy server trantorien
** File description:
** add action
*/

#include <stdbool.h>
#include <stddef.h>
#include "trantorien.h"
#include "internal.h"

bool trantorien_add_act(trantorien_t *trantorien, enum cmd_code_e cmd)
{
    bool status = false;
    action_t *action = NULL;

    if (trantorien_is_cmd_availible(trantorien) == false) {
        return false;
    }
    action = action_init(cmd, 0, NULL);
    if (action == NULL) {
        return false;
    }
    status = trantorien_place_cmd(trantorien, action);
    return status;
}
