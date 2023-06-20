/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** internal
*/

#ifndef INTERNAL_H_
    #define INTERNAL_H_

    #include "ntw.h"
    #include "zappy.h"

    #define _CL_TYPE(is_g) (is_g) ? "graphic" : "ai"
    #define _INF_MESS "INFO: client is: %s: %d\n"
    #define DEBUG_CLIENT_LOGIN(is_g, cc) _INF_MESS, _CL_TYPE(is_g), cc->id

void send_size(args_t *args, ntw_client_t *cl);
void send_id(client_t *cc, ntw_client_t *cl);

/**
** @brief update food for every trantoriens, associated or not with clients
** @param ntw
** @param trantorien
** @param cl
** @param is_and_egg
**/
void update_food(ntw_t *ntw, trantorien_t *trantorien,
    ntw_client_t *cl, bool is_and_egg);

// Update in states

bool update_client_not_connected(zappy_t *zappy, ntw_client_t *cl);
bool update_client_waiting_team_name(zappy_t *zappy, ntw_client_t *cl);
bool update_client_connected(zappy_t *zappy, ntw_client_t *cl);
bool update_client_waiting_slot_opened(zappy_t *zappy, ntw_client_t *cl);

// update by types in state connected

bool update_ai_cmd(zappy_t *zappy, ntw_client_t *cl);
bool update_graphic_cmd(zappy_t *zappy, ntw_client_t *cl);

#endif // INTERNAL_H
