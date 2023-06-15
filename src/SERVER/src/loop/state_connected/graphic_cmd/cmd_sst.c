/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** cmd_sst
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <tlcstrings.h>
#include "circular_buffer.h"
#include "trantorien.h"
#include "zappy.h"
#include "internal.h"

bool cmd_sst(zappy_t *zappy, ntw_client_t *cl, char **cmd_split)
{
    char buff[512] = {0};
    int new_freq = 0;

    if (cmd_split[1] == NULL ||
    x_strcontainc("0123456789", cmd_split[1][0]) != 1) {
        return false;
    }
    new_freq = atoi(cmd_split[1]);
    if (new_freq <= 0) {
        return false;
    }
    zappy->args->freq = new_freq;
    snprintf(buff, 511, "sst %d\n", zappy->args->freq);
    circular_buffer_write(cl->write_to_outside, buff);
    return true;
}
