/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** cmd_ebo
*/

#include <stdbool.h>
#include <stdio.h>
#include "ntw.h"
#include "map.h"
#include "internal.h"
#include "client.h"

bool cmd_ebo(ntw_t *ntw, ntw_client_t *cl)
{
    char buff[512] = {0};
    client_t *client = NULL;

    if (ntw == NULL || cl == NULL) {
        return false;
    }
    client = L_DATA(cl);
    snprintf(buff, 511, "ebo %d\n", client->id);
    broadcast_graphic(ntw, buff);
    return true;
}
