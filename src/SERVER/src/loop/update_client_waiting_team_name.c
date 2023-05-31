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
    circular_buffer_write(cl->write_to_outside, id_to_str);
    free(id_to_str);
    circular_buffer_write(cl->write_to_outside, "\n");
}

static void send_size(args_t *args, ntw_client_t *cl)
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

static bool update(char *tmp, client_t *cc, ntw_client_t *cl, args_t *args)
{
    strncpy(cc->name, tmp, sizeof(cc->name) - 1);
    send_id(cc, cl);
    send_size(args, cl);
    cc->state = CONNECTED;
    printf("%s%s%s\n", "INFO: receving team name'", cc->name,
        "', sending id + x y...");
    if (strcmp(cc->name, "GRAPHIC\n") == 0) {
        cc->type = GRAPHIC;
        printf("%s\n", "INFO: client is graphic");
    } else {
        cc->type = AI;
        printf("%s\n", "INFO: client is ai");
    }
    return true;
}

<<<<<<< HEAD
bool update_client_waiting_team_name(__attribute__((unused)) ntw_t *ntw,
    ntw_client_t *cl, args_t *args)
=======
bool update_client_waiting_team_name(zappy_t *zappy, ntw_client_t *cl)
>>>>>>> dev
{
    char *tmp = NULL;
    client_t *cc = NULL;
    bool status = false;

    if (cl == NULL || zappy == NULL) {
        return true;
    }
    cc = cl->data;
    if (circular_buffer_is_read_ready(cl->read_from_outside) == false) {
        return true;
    }
    tmp = circular_buffer_read(cl->read_from_outside);
    if (tmp == NULL) {
        return false;
    }
<<<<<<< HEAD
    status = update(tmp, cc, cl, args);
=======
    status = update(tmp, cc, cl, zappy->args);
>>>>>>> dev
    free(tmp);
    return status;
}
