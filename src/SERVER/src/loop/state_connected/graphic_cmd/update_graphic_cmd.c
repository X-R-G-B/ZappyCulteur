/*
** EPITECH PROJECT, 2023
** zappy server loop
** File description:
** graphic_cmd update
*/

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "circular_buffer.h"
#include "internal.h"
#include "llog.h"
#include "ntw.h"
#include "tlcstrings.h"
#include "command_reponses.h"
#include "broadcast_events.h"

static const char cmds_graphic[NB_CMD_AVAILIBLE][6] = {
    "msz\n",
    "bct",
    "mct\n",
    "tna\n",
    "ppo",
    "plv",
    "pin",
    "sgt\n",
    "sst",
    "",
};

static bool
(*graphic_funcs[NB_CMD_AVAILIBLE])
(zappy_t *zappy, ntw_client_t *cl, char **) = {
    cmd_msz,
    cmd_bct,
    cmd_mct,
    cmd_tna,
    cmd_ppo,
    cmd_plv,
    cmd_pin,
    cmd_sgt,
    cmd_sst,
    NULL,
};

static void debug_error(ntw_client_t *cl, bool is_entered)
{
    if (is_entered == false) {
        cmd_suc(cl);
        llog_write_fd(STDERR_FILENO, LLOG_WARNING, "unknown command");
        llog_write_f(LOG_FILE_GUIC, LLOG_WARNING, "unknown command");
    } else {
        cmd_sbp(cl);
        llog_write_fd(STDERR_FILENO, LLOG_WARNING, "bad command syntax");
        llog_write_f(LOG_FILE_GUIC, LLOG_WARNING, "bad command syntax");
    }
}

static bool update_cmd(zappy_t *zappy, ntw_client_t *cl, char **cmd_split)
{
    bool is_entered = false;
    bool status = false;

    for (int i = 0; cmds_graphic[i][0] != '\0'; i++) {
        if (strcmp(cmd_split[0], cmds_graphic[i]) == 0) {
            status = graphic_funcs[i](zappy, cl, cmd_split);
            is_entered = true;
            break;
        }
    }
    if (status == true) {
        return status;
    }
    debug_error(cl, is_entered);
    return true;
}

bool update_graphic_cmd(zappy_t *zappy, ntw_client_t *cl)
{
    char **cmd_split = NULL;
    char *tmp = NULL;
    bool status = false;

    if (zappy == NULL || cl == NULL) {
        return true;
    }
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
