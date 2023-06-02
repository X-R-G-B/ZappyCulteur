/*
** EPITECH PROJECT, 2023
** zappy server trantorien
** File description:
** internal header
*/

#ifndef INTERNAL_H_
    #define INTERNAL_H_

    #include "map.h"
    #include "trantorien.h"

action_t *action_init(enum cmd_code_e, enum ressource_e object,
    char *broadcast_msg);

void action_destroy(action_t *action);

bool trantorien_is_cmd_availible(trantorien_t *trantorien);
bool trantorien_place_cmd(trantorien_t *trantorien, action_t *action);

#endif
