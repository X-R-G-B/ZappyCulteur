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
#include "client.h"
#include "internal.h"

static void update_tiles_tr_pos(zappy_t *zappy)
{
    int map_i = 0;
    client_t *cl = NULL;
    trantorien_t *trantorien = NULL;

    for (int i = 0; i < zappy->map->width * zappy->map->height; i++) {
        zappy->map->tiles[i].ressources[PLAYER] = 0;
    }
    for (L_EACH(data, zappy->ntw->clients)) {
        cl = L_DATA(L_DATAT(ntw_client_t *, data));
        if (cl == NULL || cl->type != AI || cl->cl.ai.trantorien == NULL) {
            continue;
        }
        trantorien = cl->cl.ai.trantorien;
        map_index_x_y_to_i(zappy->map, trantorien->x, trantorien->y, &map_i);
        zappy->map->tiles[map_i].ressources[PLAYER] += 1;
    }
}

int command_look_around(trantorien_t *trantorien, zappy_t *zappy,
                        ntw_client_t *cl, action_t *action)
{
    if (trantorien == NULL || zappy == NULL || cl == NULL || action == NULL) {
        return EXIT_FAILURE;
    }
    update_tiles_tr_pos(zappy);
    look_around(trantorien, trantorien->level, zappy->map, cl);
    return EXIT_SUCCESS;
}
