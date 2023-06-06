/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** command_look_around
*/

#include <stddef.h>
#include <stdlib.h>
#include "ntw.h"
#include "zappy.h"
#include "trantorien.h"
#include "map.h"
#include "tlcstdlibs.h"

static const char *ressources_name[MAX_NB_RESOURCES] = {
    "food",
    "linemate",
    "deraumere",
    "sibur",
    "mendiane",
    "phiras",
    "thystame",
    "player",
    "egg"
};

static void send_tile_single_ressource(ntw_client_t *cl, int ressources,
    int ressource_nbr)
{
    for (int i = 0; i < ressource_nbr; i++) {
        circular_buffer_write(cl->write_to_outside, ressources_name[ressources]);
        circular_buffer_write(cl->write_to_outside, " ");
    }
}

void send_tile_ressources(ntw_client_t *cl, map_tile_t *tile, int message_state)
{
    if (message_state == -1) {
        circular_buffer_write(cl->write_to_outside, "[");
    } else if (message_state != -1) {
        circular_buffer_write(cl->write_to_outside, ",");
    }
    for (int i = 0; i < MAX_RESSOURCE; i++) {
        send_tile_single_ressource(cl, i, tile->ressources[i]);
    }
    if (message_state == 1)
        circular_buffer_write(cl->write_to_outside, "]\n");
}

int command_look_around(trantorien_t *trantorien, zappy_t *zappy,
                        ntw_client_t *cl, action_t *action)
{
    static void (*look_around_commands[])(trantorien_t *, int,
            map_t *, ntw_client_t *) = {
        look_north_tiles_ressources,
        look_east_tiles_ressources,
        look_south_tiles_ressources,
        look_west_tiles_ressources,
        NULL
    };

    if (trantorien == NULL || zappy == NULL || cl == NULL || action == NULL)
        return EXIT_FAILURE;
    for (int lvl = 0; lvl <= trantorien->level; lvl++) {
        look_around_commands[trantorien->direction - 1](trantorien, lvl,
            zappy->map, cl);
    }
    return EXIT_SUCCESS;
}
