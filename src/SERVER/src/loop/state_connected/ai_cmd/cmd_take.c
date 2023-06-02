/*
** EPITECH PROJECT, 2023
** zappy server ai cmd
** File description:
** Take
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "circular_buffer.h"
#include "client.h"
#include "map.h"
#include "tlcstdlibs.h"
#include "tlcstrings.h"
#include "zappy.h"
#include "internal.h"
#include "trantorien.h"

static const char *ressources_map[] = {
    "food\n",
    "linemate\n",
    "deraumere\n",
    "sibur\n",
    "mendiane\n",
    "phiras\n",
    "thystame\n",
};

static bool handle_trantorien_take(trantorien_t *trantorien, int i)
{
    if (trantorien_add_act_take(trantorien, i) == false) {
        return false;
    }
    return true;
}

bool cmd_take(__attribute__((unused)) zappy_t *zappy, ntw_client_t *cl,
    char **cmd_split)
{
    client_t *cc = cl->data;

    if (cmd_split[1] == NULL || x_strendswith(cmd_split[1], "\n") == 0) {
        return false;
    }
    for (int i = 0; i < MAX_NB_RESOURCES; i++) {
        if (strcmp(cmd_split[1], ressources_map[i]) == 0) {
            return handle_trantorien_take(cc->cl.ai.trantorien, i);
        }
    }
    return false;
}
