/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** set_object_down
*/

#include <stddef.h>
#include <stdlib.h>
#include "ntw.h"
#include "zappy.h"
#include "trantorien.h"
#include "map.h"

int command_set_object_down(trantorien_t *trantorien, zappy_t *zappy,
                        ntw_client_t *cl, action_t *action)
{
    int i = 0;

    if (trantorien == NULL || zappy == NULL || cl == NULL || action == NULL)
        return EXIT_FAILURE;
    if (trantorien->ressources[action->param.object] > 0) {
        trantorien->ressources[action->param.object] -= 1;
        map_index_x_y_to_i(zappy->map, trantorien->x, trantorien->y, &i);
        zappy->map[i].tiles->ressources[action->param.object] += 1;
        ntw_send(cl, "ok\n");
    } else {
        ntw_send(cl, "ko\n");
    }
    return EXIT_SUCCESS;
}