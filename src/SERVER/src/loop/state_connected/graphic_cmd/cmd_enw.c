/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** cmd_enw
*/

#include <stdbool.h>
#include <stdio.h>
#include "ntw.h"
#include "internal.h"
#include "client.h"

bool cmd_enw(ntw_t *ntw, trantorien_t *tr, trantorien_t *parent)
{
    char buff[512] = {0};

    if (ntw == NULL || tr == NULL || parent == NULL) {
        return false;
    }
    snprintf(buff, 511, "enw %d %d %d %d\n",
        tr->id, parent->id, tr->x, tr->y);
    broadcast_graphic(ntw, buff);
    return true;
}
