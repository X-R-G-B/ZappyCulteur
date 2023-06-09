/*
** EPITECH PROJECT, 2023
** zappy server trantorien
** File description:
** add action broadcast
*/

#include <stdbool.h>
#include <stddef.h>
#include "trantorien.h"
#include "internal.h"

bool trantorien_add_act_broadcast(trantorien_t *trantorien, char *msg)
{
    bool status = false;
    action_t *action = NULL;

    if (msg == NULL || trantorien_is_cmd_availible(trantorien) == false) {
        return false;
    }
    action = action_init(BROADCAST, 0, msg);
    if (action == NULL) {
        return false;
    }
    status = trantorien_place_cmd(trantorien, action);
    return status;
}
