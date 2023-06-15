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
#include <tlcllists.h>
#include "circular_buffer.h"
#include "trantorien.h"
#include "zappy.h"
#include "internal.h"

static bool is_team_inside_list(void *data, void *to_find)
{
    if (x_strcmp(data, to_find) == 0)
        return true;
    return false;
}

bool cmd_tna(zappy_t *zappy, ntw_client_t *cl,
    __attribute__((unused)) char **cmd_split)
{
    char buff[512] = {0};
    list_t *teams_sent = NULL;
    char *team_name = NULL;

    teams_sent = list_create();
    for (L_EACH(data, zappy->args->teams_name)) {
        if (list_find_f(teams_sent,
        is_team_inside_list, L_DATA(data)).node_ptr != NULL)
            continue;
        team_name = L_DATA(data);
        list_append(teams_sent, team_name, NULL, NULL);
        snprintf(buff, 511, "tna %s\n", team_name);
        circular_buffer_write(cl->write_to_outside, buff);
    }
    list_delete(teams_sent);
    return true;
}
