/*
** EPITECH PROJECT, 2023
** zappy server global
** File description:
** loop
*/

#include <stdbool.h>
#include <string.h>
#include "args.h"
#include "circular_buffer.h"
#include "client.h"
#include "ntw.h"
#include "tlcllists.h"
#include "zappy.h"

static bool update_client(ntw_t *ntw, ntw_client_t *cl, args_t *args)
{
    client_t *cc = NULL;
    bool (*funcs[3])(ntw_t *ntw, ntw_client_t *cl, args_t *args) = {
        update_client_not_connected,
        update_client_waiting_team_name,
        update_client_connected
    };

    if (cl == NULL) {
        return false;
    }
    cc = cl->data;
    return funcs[cc->state](ntw, cl, args);
}

bool loop(ntw_t *ntw, args_t *args)
{
    ntw_client_t *cl = NULL;
    bool status = true;

    for (L_EACH(client, ntw->clients)) {
        cl = L_DATA(client);
        status = update_client(ntw, cl, args) & status;
    }
    return !status;
}
