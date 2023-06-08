/*
** EPITECH PROJECT, 2023
** zappy server ai cmd
** File description:
** Broadcast
*/

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "circular_buffer.h"
#include "client.h"
#include "zappy.h"
#include "internal.h"
#include "trantorien.h"

bool cmd_broadcast(__attribute__((unused)) zappy_t *zappy, ntw_client_t *cl,
    char *cmd)
{
    client_t *cc = cl->data;
    char *tmp = NULL;
    char *msg = NULL;

    tmp = strchr(cmd, ' ');
    if (tmp == NULL) {
        return false;
    }
    msg = strdup(tmp + 1);
    tmp = strchr(msg, '\n');
    if (tmp == NULL) {
        return false;
    }
    tmp[0] = '\0';
    if (trantorien_add_act_broadcast(cc->cl.ai.trantorien, msg) == false) {
        free(msg);
        return false;
    }
    return true;
}
