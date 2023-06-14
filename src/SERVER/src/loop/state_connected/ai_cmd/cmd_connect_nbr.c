/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** cmd_connect_nbr
*/

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include "ntw.h"
#include "zappy.h"
#include "client.h"
#include "tlcstrings.h"

static trantorien_t *get_trantorien_src(ntw_client_t *cl)
{
    client_t *client = NULL;

    client = L_DATA(cl);
    if (client == NULL || client->type != AI) {
        return NULL;
    }
    return client->cl.ai.trantorien;
}

bool cmd_connect_nbr(zappy_t *zappy, ntw_client_t *cl, char **cmd_split)
{
    trantorien_t *tr = NULL;
    trantorien_t *tr_src = NULL;
    int nbr_connections = 0;
    char buff[512] = {0};

    if (zappy == NULL || cl == NULL || cmd_split == NULL)
        return false;
    tr_src = get_trantorien_src(cl);
    if (tr_src == NULL)
        return false;
    for (L_EACH(data, zappy->trantoriens_available)) {
        tr = L_DATA(data);
        if (tr == NULL || x_strcmp(tr->team_name, tr_src->team_name) != 0)
            continue;
        nbr_connections++;
    }
    snprintf(buff, 511, "%d\n", nbr_connections);
    circular_buffer_write(cl->write_to_outside, buff);
    return true;
}
