/*
** EPITECH PROJECT, 2023
** zappy server trantorien
** File description:
** add action take
*/

#include <stdbool.h>
#include <stddef.h>
#include "map.h"
#include "trantorien.h"
#include "internal.h"

bool trantorien_add_act_take(trantorien_t *trantorien,
    enum ressource_e object)
{
    bool status = false;
    action_t *action = NULL;

    if (trantorien_is_cmd_availible(trantorien) == false) {
        return false;
    }
    action = action_init(TAKE, object, NULL);
    if (action == NULL) {
        return false;
    }
    status = trantorien_place_cmd(trantorien, action);
    return status;
}
