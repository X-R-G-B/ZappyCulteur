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

bool update_client_not_connected(__attribute__((unused)) ntw_t *ntw,
    ntw_client_t *cl, __attribute__((unused)) args_t *args)
{
    client_t *cc = cl->data;

    circular_buffer_write(cl->write_to_outside, "WELCOME\n");
    cc->state = WAITING_TEAM_NAME;
    printf("%s\n", "INFO: new connection, sending welcome...");
    return true;
}