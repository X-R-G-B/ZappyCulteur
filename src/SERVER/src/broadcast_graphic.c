/*
** EPITECH PROJECT, 2023
** zappy server trantorien
** File description:
** broadcast to graphic the msg
*/

#include <stdbool.h>
#include "circular_buffer.h"
#include "client.h"
#include "ntw.h"

bool broadcast_graphic(ntw_t *ntw, const char *msg)
{
    ntw_client_t *client = NULL;
    client_t *c = NULL;

    for (L_EACH(x, ntw->clients)) {
        client = L_DATA(x);
        c = L_DATA(client);
        if (c == NULL || client == NULL) {
            continue;
        }
        if (c->type != GRAPHIC) {
            continue;
        }
        circular_buffer_write(client->write_to_outside, msg);
    }
    return true;
}
