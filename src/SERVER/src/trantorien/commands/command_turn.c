/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** command_turn
*/

#include <stddef.h>
#include <stdlib.h>
#include "ntw.h"
#include "zappy.h"
#include "trantorien.h"
#include "map.h"

int command_turn_right(trantorien_t *trantorien, zappy_t *zappy,
                        ntw_client_t *cl, action_t *action)
{
    if (trantorien == NULL || zappy == NULL || cl == NULL || action == NULL) {
        circular_buffer_write(cl->write_to_outside, "ko\n");
        return EXIT_FAILURE;
    }
    trantorien->direction += 1;
    trantorien->direction %= MAX_DIRECTION;
    if (trantorien->direction == 0) {
        trantorien->direction = 1;
    }
    circular_buffer_write(cl->write_to_outside, "ok\n");
    return EXIT_SUCCESS;
}

int command_turn_left(trantorien_t *trantorien, zappy_t *zappy,
                        ntw_client_t *cl, action_t *action)
{
    if (trantorien == NULL || zappy == NULL || cl == NULL || action == NULL) {
        circular_buffer_write(cl->write_to_outside, "ko\n");
        return EXIT_FAILURE;
    }
    trantorien->direction -= 1;
    if (trantorien->direction <= 0)
        trantorien->direction += MAX_DIRECTION - 1;
    trantorien->direction %= MAX_DIRECTION;
    circular_buffer_write(cl->write_to_outside, "ok\n");
    return EXIT_SUCCESS;
}
