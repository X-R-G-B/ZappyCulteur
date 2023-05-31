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

bool cmd_msz(zappy_t *zappy, ntw_client_t *cl, char **cmd_split);
bool cmd_mct(zappy_t *zappy, ntw_client_t *cl, char **cmd_split);
bool cmd_bct(zappy_t *zappy, ntw_client_t *cl, char **cmd_split);

bool cmd_bct_x_y(zappy_t *zappy, ntw_client_t *cl, int x, int y);

#endif
