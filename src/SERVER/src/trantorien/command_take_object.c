/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** command_take_object
*/

#include <stddef.h>
#include <stdlib.h>
#include "ntw.h"
#include "zappy.h"
#include "trantorien.h"
#include "map.h"

int command_take_object(trantorien_t *trantorien, zappy_t *zappy,
                        ntw_client_t *cl, action_t *action)
{
    int i = 0;

    if (trantorien == NULL || zappy == NULL || cl == NULL || action == NULL)
        return EXIT_FAILURE;
    map_index_x_y_to_i(zappy->map, trantorien->x, trantorien->y, &i);
    if (zappy->map[i].tiles->ressources[action->param.object] > 0) {
        zappy->map[i].tiles->ressources[action->param.object] -= 1;
        trantorien->ressources[action->param.object] += 1;
        circular_buffer_write(cl->write_to_outside, "ok\n");
    } else {
        circular_buffer_write(cl->write_to_outside, "ko\n");
    }
    return EXIT_SUCCESS;
}
