/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** cmd_tna
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <tlcstrings.h>
#include "circular_buffer.h"
#include "trantorien.h"
#include "zappy.h"
#include "internal.h"

bool cmd_tna(zappy_t *zappy, ntw_client_t *cl, char **cmd_split)
{
    char buff[512] = {0};
    char *team_name = NULL;

    for (L_EACH(data, zappy->args->teams_name)) {
        team_name = L_DATA(data);
        snprintf(buff, 511, "tna %s\n", team_name);
        circular_buffer_write(cl->write_to_outside, buff);
    }
    return true;
}
