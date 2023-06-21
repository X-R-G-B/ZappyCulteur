/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** cmd_pex
*/

#include <stdbool.h>
#include <stdio.h>
#include "ntw.h"
#include "map.h"
#include "client.h"
#include "trantorien.h"
#include "zappy.h"

bool cmd_pex(ntw_t *ntw, trantorien_t *tr)
{
    char buff[512] = {0};

    if (ntw == NULL || tr == NULL) {
        return false;
    }
    snprintf(buff, 511, "pex %d\n", tr->id);
    broadcast_graphic(ntw, buff);
    return true;
}
