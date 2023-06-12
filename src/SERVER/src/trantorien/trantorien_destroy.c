/*
** EPITECH PROJECT, 2023
** zappy server trantorien
** File description:
** destroy
*/

#include <stdlib.h>
#include <string.h>
#include "trantorien.h"
#include "internal.h"

void trantorien_destroy(trantorien_t *trantorien)
{
    if (trantorien == NULL) {
        return;
    }
    for (int i = 0; i < NB_PARALLEL_ACTION; i++) {
        if (trantorien->actions[i] != NULL) {
            action_destroy(trantorien->actions[i]);
            trantorien->actions[i] = NULL;
        }
    }
    if (trantorien->team_name != NULL) {
        free(trantorien->team_name);
    }
    memset(trantorien, 0, sizeof(trantorien_t));
    free(trantorien);
}
