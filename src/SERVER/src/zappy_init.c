/*
** EPITECH PROJECT, 2023
** zappy server zappy
** File description:
** init
*/

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "args.h"
#include "map.h"
#include "ntw.h"
#include "zappy.h"

zappy_t *zappy_init(args_t *args)
{
    zappy_t *zappy = NULL;

    if (args == NULL || args->is_ok == false) {
        return NULL;
    }
    zappy = malloc(sizeof(zappy_t));
    if (zappy == NULL) {
        return NULL;
    }
    memset(zappy, 0, sizeof(zappy_t));
    zappy->args = args;
    zappy->map = map_init(args->width, args->height);
    zappy->ntw = ntw_init(args->port, args->teams_name->len, on_new_conn);
    zappy->trantoriens_available = zappy_create_initial_egg(args);
    if (zappy->ntw == NULL || zappy->map == NULL
            || zappy->trantoriens_available == NULL) {
        zappy_destroy(zappy);
        return NULL;
    }
    return zappy;
}
