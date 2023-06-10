/*
** EPITECH PROJECT, 2023
** zappy server trantorien
** File description:
** init
*/

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "tlcstrings.h"
#include "trantorien.h"

trantorien_t *trantorien_init(const char *team_name, int width, int height)
{
    trantorien_t *trantorien = NULL;

    trantorien = malloc(sizeof(trantorien_t));
    if (trantorien == NULL) {
        return NULL;
    }
    memset(trantorien, 0, sizeof(trantorien_t));
    trantorien->team_name = x_strdup(team_name);
    trantorien->level = 1;
    trantorien->alive = true;
    trantorien->direction = (rand() % (MAX_DIRECTION - 1)) + 1;
    trantorien->ressources[FOOD] = 10;
    trantorien->x = rand() % width;
    trantorien->y = rand() % height;
    return trantorien;
}
