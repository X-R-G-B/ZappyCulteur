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

<<<<<<< HEAD
static const char cmds_graphic[2][4] = {
    "msz\n",
=======
static const char cmds_graphic[4][6] = {
    "msz\n",
    "mct\n",
    "bct",
>>>>>>> dev
    "",
};

static bool
<<<<<<< HEAD
(*graphic_funcs[2])
(ntw_t *ntw, ntw_client_t *cl, args_t *args, char **) = {
    cmd_msz,
    NULL,
};

static bool update_cmd(ntw_t *ntw, ntw_client_t *cl, args_t *args, char **cmd_split)
=======
(*graphic_funcs[4])
(zappy_t *zappy, ntw_client_t *cl, char **) = {
    cmd_msz,
    cmd_mct,
    cmd_bct,
    NULL,
};

static bool update_cmd(zappy_t *zappy, ntw_client_t *cl, char **cmd_split)
>>>>>>> dev
{
    bool status = false;

    for (int i = 0; cmds_graphic[i][0] != '\0'; i++) {
        if (strcmp(cmd_split[0], cmds_graphic[i]) == 0) {
<<<<<<< HEAD
            status = graphic_funcs[i](ntw, cl, args, cmd_split);
=======
            status = graphic_funcs[i](zappy, cl, cmd_split);
>>>>>>> dev
            break;
        }
    }
    if (status == false) {
        circular_buffer_write(cl->write_to_outside, "ko\n");
        status = true;
    }
    return status;
}

<<<<<<< HEAD
bool update_graphic_cmd(ntw_t *ntw, ntw_client_t *cl, args_t *args)
=======
bool update_graphic_cmd(zappy_t *zappy, ntw_client_t *cl)
>>>>>>> dev
{
    char **cmd_split = NULL;
    char *tmp = NULL;
    bool status = false;

<<<<<<< HEAD
=======
    if (zappy == NULL || cl == NULL) {
        return true;
    }
>>>>>>> dev
    tmp = circular_buffer_read(cl->read_from_outside);
    if (tmp == NULL) {
        return true;
    }
    cmd_split = x_strsplit(tmp, " ");
    free(tmp);
    if (cmd_split == NULL) {
<<<<<<< HEAD
        free_char_2d(cmd_split);
        return true;
    }
    status = update_cmd(ntw, cl, args, cmd_split);
=======
        return true;
    }
    status = update_cmd(zappy, cl, cmd_split);
>>>>>>> dev
    free_char_2d(cmd_split);
    return status;
}
