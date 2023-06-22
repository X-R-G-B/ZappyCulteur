/*
** EPITECH PROJECT, 2023
** zappy server loop
** File description:
** update the graphical client
*/

#include <stdio.h>
#include <stdlib.h>
#include "tlcllists.h"
#include "tlcstdlibs.h"
#include "ntw.h"
#include "client.h"
#include "trantorien.h"
#include "zappy.h"
#include "broadcast_events.h"

void send_id(client_t *cc, ntw_client_t *cl)
{
    char buff[512] = {0};

    cc->id = get_id();
    snprintf(buff, 511, "%d\n", cc->id);
    circular_buffer_write(cl->write_to_outside, buff);
}

void send_size(args_t *args, ntw_client_t *cl)
{
    char *size_to_str = NULL;

    size_to_str = x_itoa(args->width);
    if (size_to_str == NULL) {
        return;
    }
    circular_buffer_write(cl->write_to_outside, size_to_str);
    free(size_to_str);
    circular_buffer_write(cl->write_to_outside, " ");
    size_to_str = x_itoa(args->height);
    if (size_to_str == NULL) {
        return;
    }
    circular_buffer_write(cl->write_to_outside, size_to_str);
    free(size_to_str);
    circular_buffer_write(cl->write_to_outside, "\n");
}

void connect_graphic_client(client_t *cc, ntw_client_t *cl, zappy_t *zappy)
{
    ntw_client_t *c_tmp = NULL;
    trantorien_t *tr = NULL;

    send_id(cc, cl);
    send_size(zappy->args, cl);
    for (L_EACH(node, zappy->ntw->clients)) {
        c_tmp = L_DATA(node);
        if (c_tmp == NULL || L_DATAT(client_t *, c_tmp)->type != AI) {
            continue;
        }
        cmd_pnw(zappy->ntw, c_tmp);
    }
    for (L_EACH(node, zappy->trantoriens_available)) {
        tr = L_DATA(node);
        if (tr == NULL) {
            continue;
        }
        cmd_enw(zappy->ntw, tr, NULL);
    }
}
