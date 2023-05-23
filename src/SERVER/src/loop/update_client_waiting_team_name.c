/*
** EPITECH PROJECT, 2023
** zappy server loop
** File description:
** waiting team name
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "args.h"
#include "circular_buffer.h"
#include "client.h"
#include "ntw.h"
#include "tlcstdlibs.h"
#include "zappy.h"

static void send_id(client_t *cc, ntw_client_t *cl)
{
    char *id_to_str = NULL;

    cc->id = get_id();
    id_to_str = x_itoa(cc->id);
    if (id_to_str == NULL) {
        return;
    }
    circular_buffer_write(cl->write_to_outside, "<--");
    circular_buffer_write(cl->write_to_outside, id_to_str);
    free(id_to_str);
    circular_buffer_write(cl->write_to_outside, "\n");
}

static void send_size(args_t *args, ntw_client_t *cl)
{
    char *size_to_str = NULL;

    circular_buffer_write(cl->write_to_outside, "<-- ");
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

static bool update(char *tmp, client_t *cc, ntw_client_t *cl, args_t *args)
{
    strncpy(cc->name, tmp, sizeof(cc->name) - 1);
    send_id(cc, cl);
    send_size(args, cl);
    cc->state = CONNECTED;
    printf("%s\n", "INFO: receving team name, sending id + x y...");
    return true;
}

bool update_client_waiting_team_name(ntw_t *ntw, ntw_client_t *cl,
    args_t *args)
{
    char *tmp = NULL;
    client_t *cc = cl->data;
    bool status = false;

    if (circular_buffer_is_read_ready(cl->read_from_outside) == false) {
        return true;
    }
    tmp = circular_buffer_read(cl->read_from_outside);
    if (tmp == NULL) {
        return false;
    }
    if (strncmp(tmp, "-->", strlen("-->")) != 0) {
        list_append(ntw->clients_to_remove, cl, NULL, NULL);
        return true;
    }
    status = update(tmp, cc, cl, args);
    free(tmp);
    return status;
}
