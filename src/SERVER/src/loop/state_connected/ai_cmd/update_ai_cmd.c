/*
** EPITECH PROJECT, 2023
** zappy server loop
** File description:
** ai_cmd update
*/

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "circular_buffer.h"
#include "client.h"
#include "tlcstrings.h"
#include "tlcutils.h"
#include "zappy.h"
#include "internal.h"

static const char cmds_graphic[NB_CMD_AVAILIBLE][6] = {
    "",
};

static bool
(*graphic_funcs[NB_CMD_AVAILIBLE])
(zappy_t *zappy, ntw_client_t *cl, char **) = {
    NULL,
};

static bool update_cmd(zappy_t *zappy, ntw_client_t *cl, char **cmd_split)
{
    bool status = false;

    for (int i = 0; cmds_graphic[i][0] != '\0'; i++) {
        if (strcmp(cmd_split[0], cmds_graphic[i]) == 0) {
            status = graphic_funcs[i](zappy, cl, cmd_split);
            break;
        }
    }
    if (status == false) {
        circular_buffer_write(cl->write_to_outside, "ko\n");
        status = true;
    }
    return status;
}

bool update_ai_cmd(zappy_t *zappy, ntw_client_t *cl)
{
    char *tmp = NULL;
    char **cmd_split = NULL;
    bool status = false;

    tmp = circular_buffer_read(cl->read_from_outside);
    if (tmp == NULL) {
        return true;
    }
    cmd_split = x_strsplit(tmp, " ");
    free(tmp);
    if (cmd_split == NULL) {
        return true;
    }
    status = update_cmd(zappy, cl, cmd_split);
    free_char_2d(cmd_split);
    return status;
}
