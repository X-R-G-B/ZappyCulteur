/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** command_inventory
*/

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "ntw.h"
#include "zappy.h"
#include "trantorien.h"

static const char *ressources_name[MAX_NB_TR_RESSOURCES] = {
    "food",
    "linemate",
    "deraumere",
    "sibur",
    "mendiane",
    "phiras",
    "thystame"
};

int command_inventory(trantorien_t *trantorien, zappy_t *zappy,
                        ntw_client_t *cl, action_t *action)
{
    char buff[512] = {0};

    if (trantorien == NULL || zappy == NULL || cl == NULL || action == NULL) {
        return EXIT_FAILURE;
    }
    circular_buffer_write(cl->write_to_outside, "[");
    for (int i = 0; i < MAX_NB_TR_RESSOURCES; i++) {
        if (i != 0) {
            circular_buffer_write(cl->write_to_outside, ", ");
        }
        snprintf(buff, 511, "%s %d", ressources_name[i],
            trantorien->ressources[i]);
        circular_buffer_write(cl->write_to_outside, buff);
    }
    circular_buffer_write(cl->write_to_outside, "]\n");
    return EXIT_SUCCESS;
}
