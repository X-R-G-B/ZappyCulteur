/*
** EPITECH PROJECT, 2023
** zappy server graphic cmd
** File description:
** ppo
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <tlcstrings.h>
#include "circular_buffer.h"
#include "tlcstdlibs.h"
#include "trantorien.h"
#include "zappy.h"
#include "internal.h"

bool cmd_ppo(zappy_t *zappy, ntw_client_t *cl, char **cmd_split)
{
    char buff[512] = {0};
    int id = 0;
    trantorien_t *trantorien = NULL;

    if (cmd_split[1] == NULL || cmd_split[1][0] != '#' ||
            x_strcontainc("0123456789", cmd_split[1][1]) == 0) {
        return false;
    }
    id = atoi(cmd_split[1] + 1);
    trantorien = zappy_trantorien_find_by_id(zappy, id);
    if (trantorien == NULL) {
        return false;
    }
    snprintf(buff, 511, "ppo %d %d\n", trantorien->x, trantorien->y);
    circular_buffer_write(cl->write_to_outside, buff);
    return true;
}