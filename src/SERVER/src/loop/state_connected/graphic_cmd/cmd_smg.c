/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** cmd_smg
*/

#include <stdbool.h>
#include <stdio.h>
#include "ntw.h"
#include "map.h"
#include "internal.h"
#include "client.h"

bool cmd_smg(ntw_t *ntw, const char *smg)
{
    char buff[512] = {0};

    if (ntw == NULL || smg == NULL) {
        return false;
    }
    snprintf(buff, 511, "smg %s\n", smg);
    broadcast_graphic(ntw, buff);
    return true;
}
