/*
** EPITECH PROJECT, 2023
** zappy server args
** File description:
** destroy
*/

#include "tlcllists.h"
#include "args.h"
#include <stdlib.h>

void args_destroy(args_t *args)
{
    if (args == NULL) {
        return;
    }
    list_delete(args->teams_name);
    args->teams_name = NULL;
    free(args);
}
