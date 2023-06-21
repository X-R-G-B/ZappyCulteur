/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** cmd_pnw
*/

#include <stdbool.h>
#include <stdio.h>
#include "client.h"
#include "internal.h"
#include "trantorien.h"

bool cmd_pnw(ntw_t *ntw, ntw_client_t *cl)
{
    char buffer[512] = {0};
    client_t *client = NULL;
    trantorien_t *tr = NULL;

    if (ntw == NULL || cl == NULL || cl->data == NULL) {
        return false;
    }
    client = cl->data;
    if (client == NULL || client->type != AI
        || client->cl.ai.trantorien == NULL) {
        return false;
    }
    tr = client->cl.ai.trantorien;
    snprintf(buffer, 511, "pnw %d %d %d %d %d %s\n", client->id,
        tr->x, tr->y, tr->direction, tr->level, tr->team_name);
    broadcast_graphic(ntw, buffer);
    return true;
}
