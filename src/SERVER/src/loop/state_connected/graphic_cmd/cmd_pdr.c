/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** cmd_pdr
*/

#include <stdbool.h>
#include <stdio.h>
#include "ntw.h"
#include "map.h"
#include "internal.h"
#include "client.h"

bool cmd_pdr(ntw_t *ntw, ntw_client_t *cl, action_t *action)
{
    char buff[512] = {0};
    client_t *client = NULL;

    if (ntw == NULL || cl == NULL || action == NULL) {
        return false;
    }
    client = L_DATA(cl);
    snprintf(buff, 511, "pdr %d %i\n", client->id, action->param.object);
    broadcast_graphic(ntw, buff);
    return true;
}
