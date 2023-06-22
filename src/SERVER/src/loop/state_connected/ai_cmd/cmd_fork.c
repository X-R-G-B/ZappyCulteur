/*
** EPITECH PROJECT, 2023
** zappy server ai cmd
** File description:
** Fork
*/

#include <stdbool.h>
#include "client.h"
#include "zappy.h"
#include "internal.h"
#include "trantorien.h"
#include "broadcast_events.h"

bool cmd_fork(__attribute__((unused)) zappy_t *zappy, ntw_client_t *cl,
    __attribute__((unused)) char **cmd_split)
{
    client_t *cc = cl->data;

    if (trantorien_add_act(cc->cl.ai.trantorien, FORK) == false) {
        return false;
    }
    return true;
}
