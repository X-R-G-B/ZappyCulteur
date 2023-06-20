/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** command_start_incantation
*/

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include "ntw.h"
#include "trantorien.h"
#include "zappy.h"
#include "client.h"
#include "command_reponses.h"

const int level_ressources[LVL_MAX - 1][PLAYER] = {
    {1, 0, 0, 0, 0, 0},
    {1, 1, 1, 0, 0, 0},
    {2, 0, 1, 0, 2, 0},
    {1, 1, 2, 0, 1, 0},
    {1, 2, 1, 3, 0, 0},
    {1, 2, 3, 0, 1, 0},
    {2, 2, 2, 2, 2, 1},
};

static void update_level_trantoriens(ntw_t *ntw, int lvl, trantorien_t *tr)
{
    client_t *cl = NULL;
    ntw_client_t *cc = NULL;
    char buff[512] = {0};

    for (L_EACH(client, ntw->clients)) {
        cc = L_DATA(client);
        cl = L_DATA(cc);
        if (cl == NULL || cl->type != AI || cl->cl.ai.trantorien == NULL ||
                cl->cl.ai.trantorien->level != lvl - 1 || cc == NULL ||
                cl->cl.ai.trantorien->x != tr->x ||
                cl->cl.ai.trantorien->y != tr->y) {
            continue;
        }
        cl->cl.ai.trantorien->level = lvl;
        cl->cl.ai.trantorien->incantation = NULL;
        snprintf(buff, 511, "Current level: %d\n%c", lvl, '\0');
        circular_buffer_write(cc->write_to_outside, buff);
    }
}

static void update_case_ressources(map_t *map, trantorien_t *trnt, int lvl,
    ntw_t *ntw)
{
    int map_index = 0;
    char buff[512] = {0};

    map_index_x_y_to_i(map, trnt->x, trnt->y, &map_index);
    for (int i = FOOD; i < PLAYER; i++) {
        map->tiles[map_index].ressources[i + LINEMATE] -=
            level_ressources[lvl - 1][i];
    }
    snprintf(buff, 511, "pie %d %d %d\n", trnt->x, trnt->y,
        trnt->level + 1);
    broadcast_graphic(ntw, buff);
}

int command_incantation(trantorien_t *trantorien, zappy_t *zappy,
    ntw_client_t *cl, action_t *action)
{
    char buff[512] = {0};

    if (trantorien == NULL || zappy == NULL || cl == NULL || action == NULL) {
        return EXIT_FAILURE;
    }
    if (check_incantation_availability(trantorien, zappy->map, zappy->ntw)
            == false) {
        circular_buffer_write(cl->write_to_outside, KO_RESPONSE);
        snprintf(buff, 511, "pie %d %d %d\n", trantorien->x,
            trantorien->y, trantorien->level);
        broadcast_graphic(zappy->ntw, buff);
        return EXIT_SUCCESS;
    }
    update_case_ressources(zappy->map, trantorien, trantorien->level,
        zappy->ntw);
    update_level_trantoriens(zappy->ntw, trantorien->level + 1, trantorien);
    return EXIT_SUCCESS;
}
