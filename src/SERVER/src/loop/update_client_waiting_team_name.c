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
#include "tlcstrings.h"
#include "args.h"
#include "circular_buffer.h"
#include "client.h"
#include "ntw.h"
#include "tlcllists.h"
#include "tlcstdlibs.h"
#include "trantorien.h"
#include "zappy.h"

static const char *graphic_team = "GRAPHIC\n";

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

bool check_client_team_ok(zappy_t *zappy, char *team_name)
{
    if (x_strlen(team_name) >= 1 &&
            team_name[x_strlen(team_name) - 1] == '\n') {
        team_name[x_strlen(team_name) - 1] = '\0';
    }
    for (L_EACH(node, zappy->args->teams_name)) {
        if (x_strcmp(L_DATA(node), team_name) == 0) {
            return true;
        }
    }
    return false;
}

static bool update(char *tmp, ntw_client_t *cl, zappy_t *zappy)
{
    client_t *cc = cl->data;
    bool is_graph = strcmp(tmp, graphic_team) == 0;

    if (strcmp(tmp, graphic_team) != 0 &&
            check_client_team_ok(zappy, tmp) == false) {
        list_append(zappy->ntw->clients_to_remove, cl, NULL, NULL);
        return true;
    }
    cc->state = CONNECTED;
    cc->type = (is_graph) ? GRAPHIC : AI;
    printf("INFO: client is: %s: %d\n", (is_graph) ? "graphic" : "ai", cc->id);
    strncpy(cc->name, tmp, sizeof(cc->name) - 1);
    send_id(cc, cl);
    send_size(zappy->args, cl);
    if (!is_graph) {
        cc->cl.ai.trantorien = trantorien_init(cc->name, cc->id,
            zappy->args->width, zappy->args->height);
    }
    return true;
}

bool update_client_waiting_team_name(zappy_t *zappy, ntw_client_t *cl)
{
    char *tmp = NULL;
    bool status = false;

    if (cl == NULL || zappy == NULL) {
        return true;
    }
    if (circular_buffer_is_read_ready(cl->read_from_outside) == false) {
        return true;
    }
    tmp = circular_buffer_read(cl->read_from_outside);
    if (tmp == NULL) {
        return false;
    }
    status = update(tmp, cl, zappy);
    free(tmp);
    return status;
}
