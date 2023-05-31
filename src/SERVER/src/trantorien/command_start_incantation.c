/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** command_start_incantation
*/

#include <stddef.h>
#include <stdlib.h>
#include "ntw.h"
#include "zappy.h"
#include "trantorien.h"
#include "map.h"
#include "client.h"
#include "tlcstdlibs.h"

static const int level_ressources[MAX_NB_RESOURCES][LVL_MAX - 1] = {
    {1, 0, 0, 0, 0, 0},
    {1, 1, 1, 0, 0, 0},
    {2, 0, 1, 0, 2, 0},
    {1, 1, 2, 0, 1, 0},
    {1, 2, 1, 3, 0, 0},
    {1, 2, 3, 0, 1, 0},
    {2, 2, 2, 2, 2, 1},
};

static const int level_players[LVL_MAX - 1] = {
    1, 2, 2, 4, 4, 6, 6
};

static bool check_incantation_lvl_availability(int trantorien_lvl, ntw_t *ntw)
{
    int nb_trantorien_lvl = 0;
    ntw_client_t *nt_cl = NULL;
    client_t *cl = NULL;
    trantorien_t *trantorien = NULL;

    for (L_EACH(client, ntw->clients)) {
        cl = L_DATA((ntw_client_t *) L_DATA(client));
        if (cl == NULL || cl->type != AI)
            continue;
        trantorien = cl->cl.ai.trantorien;
        if (trantorien != NULL && trantorien->level == trantorien_lvl)
            nb_trantorien_lvl += 1;
    }
    if (nb_trantorien_lvl < level_players[trantorien_lvl - 1])
        return false;
    return true;
}


bool check_incantation_availability(trantorien_t *trantorien, map_t *map,
    ntw_t *ntw)
{
    int map_index = 0;

    map_index_x_y_to_i(map, trantorien->x, trantorien->y, &map_index);
    for (int i = FOOD; i < MAX_NB_RESOURCES; i++) {
        if (map[map_index].tiles->ressources[i] <
            level_ressources[trantorien->level - 1][i])
            return false;
    }
    if (check_incantation_lvl_availability(trantorien->level, ntw) == false)
        return false;
    return true;
}

int command_start_incantation(trantorien_t *trantorien, zappy_t *zappy,
                        ntw_client_t *cl, action_t *action)
{
    int i = 0;
    char *level_str = NULL;

    if (trantorien == NULL || zappy == NULL || cl == NULL || action == NULL)
        return EXIT_FAILURE;
    if (check_incantation_availability(trantorien, zappy->map, zappy->ntw)
        == false) {
        circular_buffer_write(cl->write_to_outside, "ko\n");
        return EXIT_SUCCESS;
    }
    level_str = x_itoa(trantorien->level);
    if (level_str == NULL)
        return EXIT_FAILURE;
    circular_buffer_write(cl->write_to_outside, "Elevation underway Current level: ");
    circular_buffer_write(cl->write_to_outside, level_str);
    circular_buffer_write(cl->write_to_outside, "\n");
    return EXIT_SUCCESS;
}
