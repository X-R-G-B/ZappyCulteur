/*
** EPITECH PROJECT, 2023
** zappy server graphic cmd
** File description:
** msz
*/

#include <stdio.h>
#include "circular_buffer.h"
#include "zappy.h"
#include "internal.h"

bool cmd_msz(zappy_t *zappy, ntw_client_t *cl,
    __attribute__((unused)) char **cmd_split)
{
    char buff[512] = {0};

    snprintf(buff, 511, "msz %d %d\n", zappy->args->width, zappy->args->height);
    circular_buffer_write(cl->write_to_outside, buff);
    return true;
}
