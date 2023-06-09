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
#include "internal.h"

static bool (*funcs[CONNECTED + 1])(zappy_t *zappy, ntw_client_t *cl) = {
    update_client_not_connected,
    update_client_waiting_team_name,
    update_client_waiting_slot_opened,
    update_client_connected,
};

static bool update_client(zappy_t *zappy, ntw_client_t *cl, bool new_freq)
{
    client_t *cc = NULL;
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

static void update_clients_connections(ntw_t *ntw)
{
    trantorien_t *trantorien = NULL;
    client_t *cl = NULL;

    if (ntw == NULL) {
        return;
    }
    for (L_EACH(client, ntw->clients)) {
        cl = L_DATA(L_DATAT(ntw_client_t *, client));
        if (cl == NULL || cl->type != AI) {
            continue;
        }
        trantorien = cl->cl.ai.trantorien;
        if (trantorien == NULL) {
            continue;
        }
        if (trantorien->alive == false) {
            list_append(ntw->clients_to_remove, client, NULL, NULL);
        }
    }
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

static void update_trantoriens_available_food(list_t *trantoriens_available,
    bool new_freq)
{
    trantorien_t *trantorien = NULL;

    if (trantoriens_available == NULL || new_freq == false) {
        return;
    }
    for (L_EACH(data, trantoriens_available)) {
        trantorien = L_DATA(data);
        if (trantorien == NULL) {
            continue;
        }
        update_food(trantorien, NULL, new_freq);
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
        update_clients_connections(zappy->ntw);
        if (L_DATAT(client_t *, client)->type == AI) {
            update_food(L_DATAT(client_t *, client)->cl.ai.trantorien,
                cl, new_freq);
        }
    }
    update_trantoriens_available_food(zappy->trantoriens_available, new_freq);
    return !status;
}
