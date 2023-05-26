/*
** EPITECH PROJECT, 2023
** zappy server trantorien
** File description:
** destroy
*/

#include <stdlib.h>
#include <string.h>
#include "trantorien.h"

void trantorien_destroy(trantorien_t *trantorien)
{
    memset(trantorien, 0, sizeof(trantorien_t));
    free(trantorien);
}
