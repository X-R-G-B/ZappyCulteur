/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** cmd_broadcast
*/

#include <stdbool.h>
#include <stdio.h>
#include "ntw.h"
#include "map.h"
#include "internal.h"
#include "client.h"

bool cmd_pbc(ntw_t *ntw, ntw_client_t *cl, action_t *action)
{
    char buff[512] = {0};
    client_t *client = NULL;

    if (ntw == NULL || cl == NULL || action == NULL ||
            action->code != BROADCAST || action->param.broadcast_msg == NULL) {
        return false;
    }
    client = L_DATA(cl);
    if (client == NULL) {
        return false;
    }
    snprintf(buff, 511, "pbc %d %s\n",
        client->id, action->param.broadcast_msg);
    broadcast_graphic(ntw, buff);
    return true;
}
