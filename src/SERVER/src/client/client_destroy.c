/*
** EPITECH PROJECT, 2023
** zappy server client
** File description:
** destroy
*/

#include <stdio.h>
#include <unistd.h>
#include "llog.h"
#include "client.h"
#include "trantorien.h"

// TODO: proper way to delete
void client_destroy(client_t *cl)
{
    if (cl == NULL) {
        return;
    }
    if (cl->type == AI) {
        trantorien_destroy(cl->cl.ai.trantorien);
    }
    llog_write_fd(STDERR_FILENO, LLOG_INFO, "client destroyed: %d", cl->id);
}
