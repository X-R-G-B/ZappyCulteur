/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** cmd_sgt
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <tlcstrings.h>
#include "circular_buffer.h"
#include "trantorien.h"
#include "zappy.h"
#include "internal.h"

bool cmd_sgt(zappy_t *zappy, ntw_client_t *cl,
    __attribute__((unused)) char **cmd_split)
{
    char buff[512] = {0};

    snprintf(buff, 511, "sgt %d\n", zappy->args->freq);
    circular_buffer_write(cl->write_to_outside, buff);
    return true;
}
