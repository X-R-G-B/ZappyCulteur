/*
** EPITECH PROJECT, 2023
** zappy server loop
** File description:
** update waiting slot opened
*/

#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include "circular_buffer.h"
#include "tlcstrings.h"
#include "client.h"
#include "internal.h"
#include "llog.h"
#include "tlcllists.h"
#include "trantorien.h"
#include "broadcast_events.h"
#include "zappy.h"

const char *format_str = "new player ai from egg (id:%d)";

static void send_new_connection(ntw_t *ntw, ntw_client_t *cl)
{
    cmd_ebo(ntw, cl);
    cmd_pnw(ntw, cl);
}

static void send_nb_slot(list_t *tr_available, ntw_client_t *cl,
    const char *team)
{
    int nb_opend = 0;
    trantorien_t *tr;
    char buff[512] = {0};

    for (L_EACH(node, tr_available)) {
        tr = L_DATA(node);
        if (tr == NULL || x_strcmp(tr->team_name, team) != 0) {
            continue;
        }
        nb_opend++;
    }
    snprintf(buff, 511, "%d\n", nb_opend);
    circular_buffer_write(cl->write_to_outside, buff);
}

bool update_client_waiting_slot_opened(zappy_t *zappy, ntw_client_t *cl)
{
    client_t *client;

    if (cl == NULL || zappy == NULL || cl->data == NULL) {
        return true;
    }
    client = cl->data;
    if (add_client_to_trantorien(client,
            zappy->trantoriens_available) == false) {
        return true;
    }
    client->state = CONNECTED;
    client->type = AI;
    client->id = client->cl.ai.trantorien->id;
    send_nb_slot(zappy->trantoriens_available, cl, client->name);
    send_size(zappy->args, cl);
    send_new_connection(zappy->ntw, cl);
    llog_write_fd(STDERR_FILENO, LLOG_INFO, format_str, client->id);
    return true;
}
