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

    if (ntw == NULL || cl == NULL || cl->data == NULL) {
        return false;
    }
    client = cl->data;
    if (client == NULL || client->type != AI
        || client->cl.ai.trantorien == NULL) {
        return false;
    }
    sprintf(buffer, "pnw %d %d %d %d %d %s\n", client->id,
    client->cl.ai.trantorien->x, client->cl.ai.trantorien->y,
    client->cl.ai.trantorien->direction, client->cl.ai.trantorien->level,
    client->cl.ai.trantorien->team_name);
    broadcast_graphic(ntw, buffer);
    return true;
}
