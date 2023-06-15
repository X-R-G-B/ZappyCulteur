/*
** EPITECH PROJECT, 2023
** zappy server graphic cmd
** File description:
** internal header
*/

#ifndef INTERNAL_H_
    #define INTERNAL_H_

    #include <stdbool.h>
    #include "ntw.h"
    #include "args.h"
    #include "zappy.h"

    #define NB_CMD_AVAILIBLE 10

bool cmd_msz(zappy_t *zappy, ntw_client_t *cl, char **cmd_split);
bool cmd_mct(zappy_t *zappy, ntw_client_t *cl, char **cmd_split);
bool cmd_bct(zappy_t *zappy, ntw_client_t *cl, char **cmd_split);
bool cmd_ppo(zappy_t *zappy, ntw_client_t *cl, char **cmd_split);

bool cmd_bct_x_y(zappy_t *zappy, ntw_client_t *cl, int x, int y);

/**
** @brief send the name of the teams to the graphic client
** @param zappy
** @param cl
** @param cmd_split
** @return
**/
bool cmd_tna(zappy_t *zappy, ntw_client_t *cl, char **cmd_split);

/**
** @brief send the player level to the graphic client
** @param zappy
** @param cl
** @param cmd_split
** @return true if success, false otherwise
**/
bool cmd_plv(zappy_t *zappy, ntw_client_t *cl, char **cmd_split);

/**
** @brief send the player inventory to the graphic client
** @param zappy
** @param cl
** @param cmd_split
** @return true if success, false otherwise
**/
bool cmd_pin(zappy_t *zappy, ntw_client_t *cl, char **cmd_split);

/**
** @brief send the time unit to the graphic client
** @param zappy
** @param cl
** @param cmd_split
** @return true if success, false otherwise
**/
bool cmd_sgt(zappy_t *zappy, ntw_client_t *cl, char **cmd_split);

/**
** @brief send the new time unit to the graphic client
** @param zappy
** @param cl
** @param cmd_split args of the cmd, here it's the new frequency
** @return true if success, false otherwise
**/
bool cmd_sst(zappy_t *zappy, ntw_client_t *cl, char **cmd_split);

#endif
