/*
** EPITECH PROJECT, 2023
** zappy server trantorien
** File description:
** is cmd place dispo
*/

#include <stdbool.h>
#include <stddef.h>
#include "trantorien.h"
#include "internal.h"

bool trantorien_is_cmd_availible(trantorien_t *trantorien)
{
    bool is_cmd_availible = false;

    if (trantorien == NULL) {
        return false;
    }
    for (int i = 0; i < NB_PARALLEL_ACTION; i++) {
        if (trantorien->actions[i] == NULL) {
            is_cmd_availible = true;
            break;
        }
    }
    return is_cmd_availible;
}
