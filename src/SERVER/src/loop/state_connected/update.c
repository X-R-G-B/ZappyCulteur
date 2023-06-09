/*
** EPITECH PROJECT, 2023
** zappy server loop
** File description:
** update
*/

#include <stdbool.h>
#include "circular_buffer.h"
#include "client.h"
#include "args.h"
#include "ntw.h"
#include "zappy.h"
#include "../internal.h"

bool update_client_connected(zappy_t *zappy, ntw_client_t *cl)
{
    client_t *cc = cl->data;
    bool status = false;

    if (circular_buffer_is_read_ready(cl->read_from_outside) == false) {
        return true;
    }
    if (cc->type == GRAPHIC) {
        status = update_graphic_cmd(zappy, cl);
    } else if (cc->type == AI) {
        status = update_ai_cmd(zappy, cl);
    } else {
        return false;
    }
    return status;
}
