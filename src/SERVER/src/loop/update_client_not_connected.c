/*
** EPITECH PROJECT, 2023
** zappy server loop
** File description:
** update client when not connected
*/

#include <stdio.h>
#include <unistd.h>
#include "args.h"
#include "llog.h"
#include "ntw.h"
#include "client.h"
#include "tlcllists.h"
#include "zappy.h"

static const char *str_info = "new connection, sending welcome...";

static const char *str_refuse = "new connection refused because server "
                                "max paramater is reached";

static void accept_connect(zappy_t *zappy, ntw_client_t *cl)
{
    client_t *cc = NULL;

    cc = cl->data;
    cc->height = zappy->args->height;
    cc->width = zappy->args->width;
    circular_buffer_write(cl->write_to_outside, "WELCOME\n");
    cc->state = WAITING_TEAM_NAME;
    llog_write_fd(STDERR_FILENO, LLOG_INFO, "%s", str_info);
    zappy->args->client_max--;
}

static void refuse_connect(zappy_t *zappy, ntw_client_t *cl)
{
    llog_write_fd(STDERR_FILENO, LLOG_WARNING, "%s", str_refuse);
    list_append(zappy->ntw->clients_to_remove, cl, NULL, NULL);
}

bool update_client_not_connected(zappy_t *zappy, ntw_client_t *cl)
{

    if (cl == NULL || zappy == NULL) {
        return true;
    }
    if (zappy->args->client_max == 0) {
        refuse_connect(zappy, cl);
        return true;
    }
    accept_connect(zappy, cl);
    return true;
}
