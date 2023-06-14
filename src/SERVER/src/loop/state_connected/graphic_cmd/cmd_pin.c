/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** cmd_pin
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <tlcstrings.h>
#include "circular_buffer.h"
#include "trantorien.h"
#include "zappy.h"
#include "internal.h"

static void send_id(ntw_client_t *cl, int id)
{
    char buff[512] = {0};

    snprintf(buff, 511, "pin %d ",id);
    circular_buffer_write(cl->write_to_outside, buff);
}

static bool send_pos(zappy_t *zappy, ntw_client_t *cl, int x, int y)
{
    char buff[512] = {0};

    if (x >= zappy->map->width || y >= zappy->map->height) {
        return false;
    }
    snprintf(buff, 511, "%d %d", x, y);
    circular_buffer_write(cl->write_to_outside, buff);
    return true;
}

static void send_tr_ressources(ntw_client_t *cl, trantorien_t *trantorien)
{
    char buff[512] = {0};

    snprintf(buff, 511, " %d %d %d %d %d %d %d\n",
        trantorien->ressources[FOOD],
        trantorien->ressources[LINEMATE],
        trantorien->ressources[DERAUMERE],
        trantorien->ressources[SIBUR],
        trantorien->ressources[MENDIANE],
        trantorien->ressources[PHIRAS],
        trantorien->ressources[THYSTAME]
    );
    circular_buffer_write(cl->write_to_outside, buff);
}

bool cmd_pin(zappy_t *zappy, ntw_client_t *cl, char **cmd_split)
{
    int id = 0;
    trantorien_t *trantorien = NULL;

    if (cmd_split[1] == NULL ||
    x_strcontainc("0123456789", cmd_split[1][1]) == 0) {
        return false;
    }
    id = atoi(cmd_split[1] + 1);
    trantorien = zappy_trantorien_find_by_id(zappy, id);
    if (trantorien == NULL) {
        return false;
    }
    send_id(cl, id);
    if (send_pos(zappy, cl, trantorien->x, trantorien->y) != true) {
        return false;
    }
    send_tr_ressources(cl, trantorien);
    return true;
}
