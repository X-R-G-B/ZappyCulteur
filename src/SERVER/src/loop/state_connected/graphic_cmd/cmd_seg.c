/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** cmd_seg
*/

#include <stdbool.h>
#include <stdio.h>
#include "ntw.h"
#include "map.h"
#include "internal.h"
#include "client.h"

bool cmd_seg(ntw_t *ntw, client_t *cl)
{
    char buff[512] = {0};

    if (ntw == NULL || cl == NULL) {
        return false;
    }
    snprintf(buff, 511, "seg %s\n", cl->cl.ai.trantorien->team_name);
    broadcast_graphic(ntw, buff);
    return true;
}
