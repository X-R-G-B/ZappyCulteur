/*
** EPITECH PROJECT, 2023
** zappy server ai cmd
** File description:
** Incantation
*/

#include <stdbool.h>
#include "client.h"
#include "zappy.h"
#include "internal.h"
#include "trantorien.h"

bool cmd_incantation(__attribute__((unused)) zappy_t *zappy, ntw_client_t *cl,
    __attribute__((unused)) char **cmd_split)
{
    client_t *cc = cl->data;

    if (trantorien_add_act(cc->cl.ai.trantorien, INCANTATION) == false ||
            check_incantation_availability(cc->cl.ai.trantorien,
            zappy->map, zappy->ntw) == false) {
        return false;
    }
    return true;
}
