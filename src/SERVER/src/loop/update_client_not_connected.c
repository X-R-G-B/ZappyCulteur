/*
** EPITECH PROJECT, 2023
** zappy server loop
** File description:
** update client when not connected
*/

#include <stdio.h>
#include "args.h"
#include "ntw.h"
#include "client.h"
#include "zappy.h"

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
    printf("%s\n", "INFO: new connection, sending welcome...");
    return true;
}
