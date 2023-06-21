/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** cmd_pdi
*/

#include <stdbool.h>
#include <stdio.h>
#include "ntw.h"
#include "map.h"
#include "internal.h"
#include "client.h"

bool cmd_pdi(ntw_t *ntw, int id)
{
    char buff[512] = {0};

    if (ntw == NULL) {
        return false;
    }
    snprintf(buff, 511, "pdi %d\n", id);
    broadcast_graphic(ntw, buff);
    return true;
}
