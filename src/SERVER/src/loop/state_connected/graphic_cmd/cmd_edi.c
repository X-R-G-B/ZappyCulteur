/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** cmd_edi
*/

#include <stdbool.h>
#include <stdio.h>
#include "ntw.h"
#include "map.h"
#include "internal.h"
#include "client.h"

bool cmd_edi(ntw_t *ntw, int id)
{
    char buff[512] = {0};

    if (ntw == NULL) {
        return false;
    }
    snprintf(buff, 511, "edi %d\n", id);
    broadcast_graphic(ntw, buff);
    return true;
}
