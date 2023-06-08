/*
** EPITECH PROJECT, 2023
** zappy server loop
** File description:
** ai_cmd update
*/

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "circular_buffer.h"
#include "client.h"
#include "tlcstrings.h"
#include "tlcutils.h"
#include "zappy.h"
#include "internal.h"

static const char cmds_graphic[NB_CMD_AVAILIBLE][14] = {
    "Forward\n",
    "Left\n",
    "Right\n",
    "Inventory\n",
    "Look\n",
    "Fork\n",
    "Eject\n",
    "Incantation\n",
    "Take",
    "Set",
    "",
};

static const char cmds_broadcast[] = "Broadcast";

static bool
(*graphic_funcs[NB_CMD_AVAILIBLE])
(zappy_t *zappy, ntw_client_t *cl, char **) = {
    cmd_forward,
    cmd_left,
    cmd_right,
    cmd_inventory,
    cmd_look,
    cmd_fork,
    cmd_eject,
    cmd_incantation,
    cmd_take,
    cmd_set,
    NULL,
};

static bool update_cmd(zappy_t *zappy, ntw_client_t *cl, char **cmd_split,
    char *cmd)
{
    bool status = false;

    for (int i = 0; cmds_graphic[i][0] != '\0'; i++) {
        if (strcmp(cmd_split[0], cmds_graphic[i]) == 0) {
            status = graphic_funcs[i](zappy, cl, cmd_split);
            break;
        }
    }
    if (status == false && strcmp(cmd_split[0], cmds_broadcast) == 0) {
        status = cmd_broadcast(zappy, cl, cmd);
    }
    if (status == false) {
        circular_buffer_write(cl->write_to_outside, KO_RESPONSE);
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
    if (cmd_split == NULL) {
        free(tmp);
        return true;
    }
    status = update_cmd(zappy, cl, cmd_split, tmp);
    free(tmp);
    free_char_2d(cmd_split);
    return status;
}
