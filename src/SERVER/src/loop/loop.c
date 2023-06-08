/*
** EPITECH PROJECT, 2023
** zappy server global
** File description:
** loop
*/

#include <stdbool.h>
#include "args.h"
#include "client.h"
#include "map.h"
#include "ntw.h"
#include "tlcllists.h"
#include "trantorien.h"
#include "zappy.h"

static bool update_client(zappy_t *zappy, ntw_client_t *cl, bool new_freq)
{
    client_t *cc = NULL;
    bool (*funcs[3])(zappy_t *zappy, ntw_client_t *cl) = {
        update_client_not_connected,
        update_client_waiting_team_name,
        update_client_connected
    };
    bool status = false;

    if (cl == NULL) {
        return false;
    }
    cc = cl->data;
    status = funcs[cc->state](zappy, cl);
    if (new_freq) {
        trantorien_reduce_freq(cc->cl.ai.trantorien, zappy, cl);
    }
    return status;
}

static void check_ressources(zappy_t *zappy, bool new_freq)
{
    if (new_freq == true) {
        zappy->before_add_resources--;
    }
    if (zappy->before_add_resources <= 0) {
        map_add_ressources(zappy->map);
        zappy->before_add_resources = NB_FREQ_BEFORE_RESOURCE;
    }
}

bool loop(zappy_t *zappy, bool new_freq)
{
    ntw_client_t *cl = NULL;
    bool status = true;

    check_ressources(zappy, new_freq);
    for (L_EACH(client, zappy->ntw->clients)) {
        cl = L_DATA(client);
        if (cl == NULL) {
            continue;
        }
        status = update_client(zappy, cl, new_freq) & status;
    }
    return !status;
}
