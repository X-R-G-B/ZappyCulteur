/*
** EPITECH PROJECT, 2023
** zappy server ai_cmd
** File description:
** cmd internal
*/

#ifndef INTERNAL_H_
    #define INTERNAL_H_

    #include <stdbool.h>
    #include "zappy.h"
    #include "ntw.h"

    #define NB_CMD_AVAILIBLE 2

enum cmd_code_e {
    FORWARD = 0,
};

bool cmd_forward(zappy_t *zappy, ntw_client_t *cl, char **cmd_split);

#endif
