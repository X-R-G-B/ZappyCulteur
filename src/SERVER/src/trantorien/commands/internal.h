/*
** EPITECH PROJECT, 2023
** zappy server trantorien command
** File description:
** internal header
*/

#ifndef CMD_INTERNAL_H_
    #define CMD_INTERNAL_H_

    #include "ntw.h"
    #include "trantorien.h"
    #include "map.h"


/**
** @brief look command for trantorien direction
**
** @param trantorien
** @param lvl
** @param map
** @param cl
**
** @note write the result of the look command in client circular buffer
**/
void look_around(trantorien_t *tr, int lvl, map_t *map, ntw_client_t *cl);

/**
** @brief look command
**
** @param trantorien
** @param zappy
** @param cl
** @param action
** @return int
**/
int command_look_around(trantorien_t *trantorien, zappy_t *zappy,
                        ntw_client_t *cl, action_t *action);

/**
** @brief move command
**
** @param trantorien
** @param zappy
** @param cl
** @param action
** @return int
**
** @note move the trantorien in the direction he is facing
**/
int command_move(trantorien_t *trantorien, zappy_t *zappy,
                        ntw_client_t *cl, action_t *action);

/**
** @brief set object down command
**
** @param trantorien
** @param zappy
** @param cl
** @param action
** @return int
**/
int command_set_object_down(trantorien_t *trantorien, zappy_t *zappy,
                        ntw_client_t *cl, action_t *action);

/**
** @brief start incantation command
**
** @param trantorien
** @param zappy
** @param cl
** @param action
** @return int
**/
int command_incantation(trantorien_t *trantorien, zappy_t *zappy,
                        ntw_client_t *cl, action_t *action);

/**
** @brief take object command
**
** @param trantorien
** @param zappy
** @param cl
** @param action
** @return int
**
** @note take the object on the tile the trantorien is standing on
**/
int command_take_object(trantorien_t *trantorien, zappy_t *zappy,
                        ntw_client_t *cl, action_t *action);

/**
** @brief turn right command
**
** @param trantorien
** @param zappy
** @param cl
** @param action
** @return int
**/
int command_turn_right(trantorien_t *trantorien, zappy_t *zappy,
                        ntw_client_t *cl, action_t *action);

/**
** @brief turn left command
**
** @param trantorien
** @param zappy
** @param cl
** @param action
** @return int
**/
int command_turn_left(trantorien_t *trantorien, zappy_t *zappy,
                        ntw_client_t *cl, action_t *action);

/**
** @brief inventory command, send the inventory of the trantorien to the client
**
** @param trantorien
** @param zappy
** @param cl
** @param action
** @return int
**/
int command_inventory(trantorien_t *trantorien, zappy_t *zappy,
                        ntw_client_t *cl, action_t *action);


/**
** @brief broadcast command, send message to other trnt
**
** @param trantorien
** @param zappy
** @param cl
** @param action
** @return int
**/
int command_broadcast(trantorien_t *trnt, zappy_t *zappy,
    ntw_client_t *cl, action_t *action);

/**
** @brief fork command, create a new trantorien
**
** @param trantorien
** @param zappy
** @param cl
** @param action
** @return int
**/
int command_fork(trantorien_t *trantorien, zappy_t *zappy,
    ntw_client_t *cl, action_t *action);

/**
** @brief eject command, eject the trantorien in the direction he is facing
**
** @param trantorien
** @param zappy
** @param cl
** @param action
** @return int
**/
int command_eject(trantorien_t *trantorien, zappy_t *zappy,
ntw_client_t *cl, action_t *action);

#endif
