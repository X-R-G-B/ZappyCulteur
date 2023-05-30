/*
** EPITECH PROJECT, 2023
** zappy server loop
** File description:
** graphic_cmd update
*/

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "circular_buffer.h"
#include "internal.h"
#include "tlcstrings.h"
#include "tlcutils.h"
#include "zappy.h"

static const char cmds_graphic[2][4] = {
    "msz\n",
    "",
};

static bool
(*graphic_funcs[2])
(ntw_t *ntw, ntw_client_t *cl, args_t *args, char **) = {
    cmd_msz,
    NULL,
};

static bool update_cmd(ntw_t *ntw, ntw_client_t *cl, args_t *args, char **cmd_split)
{
    bool status = false;

    for (int i = 0; cmds_graphic[i][0] != '\0'; i++) {
        if (strcmp(cmd_split[0], cmds_graphic[i]) == 0) {
            status = graphic_funcs[i](ntw, cl, args, cmd_split);
            break;
        }
    }
    if (status == false) {
        circular_buffer_write(cl->write_to_outside, "ko\n");
        status = true;
    }
    return status;
}

bool update_graphic_cmd(ntw_t *ntw, ntw_client_t *cl, args_t *args)
{
    char **cmd_split = NULL;
    char *tmp = NULL;
    bool status = false;

    tmp = circular_buffer_read(cl->read_from_outside);
    if (tmp == NULL) {
        return true;
    }
    cmd_split = x_strsplit(tmp, " ");
    free(tmp);
    if (cmd_split == NULL) {
        free_char_2d(cmd_split);
        return true;
    }
    status = update_cmd(ntw, cl, args, cmd_split);
    free_char_2d(cmd_split);
    return status;
}