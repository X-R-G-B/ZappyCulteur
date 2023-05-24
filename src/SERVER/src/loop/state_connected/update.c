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

bool update_client_connected(ntw_t *ntw, ntw_client_t *cl, args_t *args)
{
    client_t *cc = cl->data;
    bool status = false;

    if (circular_buffer_is_read_ready(cl->read_from_outside) == false) {
        return true;
    }
    if (cc->type == GRAPHIC) {
        status = update_graphic_cmd(ntw, cl, args);
    } else if (cc->type == AI) {
        status = update_ai_cmd(ntw, cl, args);
    } else {
        return false;
    }
    return status;
}
