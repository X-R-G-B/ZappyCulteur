/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** command_start_incantation
*/

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "ntw.h"
#include "zappy.h"
#include "client.h"
#include "command_reponses.h"

static const int level_ressources[LVL_MAX - 1][PLAYER] = {
    {1, 0, 0, 0, 0, 0},
    {1, 1, 1, 0, 0, 0},
    {2, 0, 1, 0, 2, 0},
    {1, 1, 2, 0, 1, 0},
    {1, 2, 1, 3, 0, 0},
    {1, 2, 3, 0, 1, 0},
    {2, 2, 2, 2, 2, 1},
};

static const int nb_level_players[LVL_MAX - 1] = {
    1, 2, 2, 4, 4, 6, 6
};

static bool check_incantation_lvl_availability(trantorien_t *ref_trnt,
    ntw_t *ntw)
{
    int nb_trantorien_lvl = 0;
    int trantorien_lvl = ref_trnt->level;
    client_t *cl = NULL;
    trantorien_t *trnt = NULL;

    for (L_EACH(client, ntw->clients)) {
        cl = L_DATA(L_DATAT(ntw_client_t *, client));
        if (cl == NULL || cl->type != AI || cl->cl.ai.trantorien == NULL) {
            continue;
        }
        trnt = cl->cl.ai.trantorien;
        if (trnt->level == ref_trnt->level && ref_trnt->x == trnt->x
                && ref_trnt->y == trnt->y) {
            nb_trantorien_lvl += 1;
        }
    }
    return (nb_trantorien_lvl == nb_level_players[trantorien_lvl - 1]);
}

bool check_incantation_availability(trantorien_t *trantorien, map_t *map,
    ntw_t *ntw)
{
    int map_index = 0;

    if (trantorien == NULL || map == NULL || ntw == NULL) {
        return false;
    }
    map_index_x_y_to_i(map, trantorien->x, trantorien->y, &map_index);
    for (int i = FOOD; i < PLAYER; i++) {
        if (map->tiles[map_index].ressources[i + LINEMATE] <
                level_ressources[trantorien->level - 1][i]) {
            return false;
        }
    }
    if (check_incantation_lvl_availability(trantorien, ntw) == false) {
        return false;
    }
    return true;
}

static void update_level_trantoriens(ntw_t *ntw, int lvl)
{
    client_t *cl = NULL;
    ntw_client_t *cc = NULL;
    char buff[512] = {0};

    for (L_EACH(client, ntw->clients)) {
        cc = L_DATA(client);
        cl = L_DATA(cc);
        if (cl == NULL || cl->type != AI || cl->cl.ai.trantorien == NULL ||
                cl->cl.ai.trantorien->level != lvl - 1 || cc == NULL) {
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
        map[map_index].tiles->ressources[i + LINEMATE] -=
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
            trantorien->y, -1);
        broadcast_graphic(zappy->ntw, buff);
        return EXIT_SUCCESS;
    }
    update_case_ressources(zappy->map, trantorien, trantorien->level,
        zappy->ntw);
    update_level_trantoriens(zappy->ntw, trantorien->level + 1);
    return EXIT_SUCCESS;
}
