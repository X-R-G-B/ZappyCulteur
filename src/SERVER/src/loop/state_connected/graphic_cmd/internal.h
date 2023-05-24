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

bool cmd_msz(ntw_t *ntw, ntw_client_t *cl, args_t *args, char **cmd_split);

#endif
