/*
** EPITECH PROJECT, 2023
** zappy server trantorien
** File description:
** action init
*/

#include <stdlib.h>
#include <string.h>
#include "trantorien.h"
#include "internal.h"

static const int freq_choices[MAX_CMD_CODE] = {
    7,
    7,
    7,
    7,
    1,
    7,
    42,
    7,
    7,
    7,
    300
};

action_t *action_init(enum cmd_code_e code, enum ressource_e object,
    char *broadcast_msg)
{
    action_t *action = NULL;

    action = malloc(sizeof(action_t));
    if (action == NULL) {
        return NULL;
    }
    memset(action, 0, sizeof(action_t));
    action->code = code;
    if (action->code == TAKE || action->code == SET) {
        action->param.object = object;
    }
    if (action->code == BROADCAST) {
        action->param.broadcast_msg = broadcast_msg;
    }
    action->freq = freq_choices[action->code];
    return action;
}
