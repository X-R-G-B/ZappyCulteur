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
#include "zappy.h"

const char *str_info = "new connection, sending welcome...";

bool update_client_not_connected(zappy_t *zappy, ntw_client_t *cl)
{
    client_t *cc = NULL;

    if (cl == NULL) {
        return true;
    }
    cc = cl->data;
    cc->height = zappy->args->height;
    cc->width = zappy->args->width;
    circular_buffer_write(cl->write_to_outside, "WELCOME\n");
    cc->state = WAITING_TEAM_NAME;
    llog_write_fd(STDERR_FILENO, LLOG_INFO, "%s", str_info);
    return true;
}
