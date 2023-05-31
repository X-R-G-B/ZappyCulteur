/*
** EPITECH PROJECT, 2023
** zappy server zappy
** File description:
** destroy
*/

#include <stdlib.h>
#include "map.h"
#include "ntw.h"
#include "zappy.h"

void zappy_destroy(zappy_t *zappy)
{
    if (zappy == NULL) {
        return;
    }
    if (zappy->map != NULL) {
        map_destroy(zappy->map);
    }
    if (zappy->ntw != NULL) {
        ntw_destroy(zappy->ntw);
    }
    free(zappy);
}
