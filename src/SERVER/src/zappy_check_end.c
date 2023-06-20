/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** zappy_check_end
*/

#include <stdbool.h>
#include "client.h"
#include "zappy.h"

bool check_end(zappy_t *zappy, bool is_end)
{
    int nb_team_alive = 0;
    client_t *cl = NULL;

    if (is_end || zappy->is_end) {
        return true;
    }
    for (L_EACH(data, zappy->ntw->clients)) {
        cl = L_DATA(L_DATAT(ntw_client_t *, data));
        if (cl == NULL || cl->type != AI || cl->cl.ai.trantorien == NULL) {
            continue;
        }
        if (cl->cl.ai.trantorien->alive == true) {
            nb_team_alive++;
        }
    }
    if (nb_team_alive <= 1 && zappy->trantoriens_available->len == 0) {
        return true;
    }
    return false;
}
