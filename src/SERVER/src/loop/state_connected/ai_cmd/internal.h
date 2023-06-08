/*
** EPITECH PROJECT, 2023
** zappy server ai_cmd
** File description:
** cmd internal
*/

#ifndef INTERNAL_H_
    #define INTERNAL_H_

    #include <stdbool.h>
    #include "map.h"
    #include "zappy.h"
    #include "ntw.h"

    #define NB_CMD_AVAILIBLE 11
    #define LEN_SIZE_MAX_RESSURCES 15

extern const char ressources_map[PLAYER][LEN_SIZE_MAX_RESSURCES];

bool cmd_forward(zappy_t *zappy, ntw_client_t *cl, char **cmd_split);
bool cmd_left(zappy_t *zappy, ntw_client_t *cl, char **cmd_split);
bool cmd_right(zappy_t *zappy, ntw_client_t *cl, char **cmd_split);
bool cmd_inventory(zappy_t *zappy, ntw_client_t *cl, char **cmd_split);
bool cmd_look(zappy_t *zappy, ntw_client_t *cl, char **cmd_split);
bool cmd_fork(zappy_t *zappy, ntw_client_t *cl, char **cmd_split);
bool cmd_eject(zappy_t *zappy, ntw_client_t *cl, char **cmd_split);
bool cmd_incantation(zappy_t *zappy, ntw_client_t *cl, char **cmd_split);
bool cmd_set(zappy_t *zappy, ntw_client_t *cl, char **cmd_split);
bool cmd_take(zappy_t *zappy, ntw_client_t *cl, char **cmd_split);

bool cmd_broadcast(zappy_t *zappy, ntw_client_t *cl, char *cmd);

#endif
