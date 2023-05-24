/*
** EPITECH PROJECT, 2022
** (my) Tiny Lib C
** File description:
** delete the list
*/

#include <stddef.h>
#include <stdlib.h>
#include "tlcllists.h"

void list_delete(list_t *list)
{
    node_t *curr = NULL;

    if (list == NULL) {
        return;
    }
    curr = L_FIRST(list);
    for (node_t *tmp = NULL; curr != NULL; curr = tmp) {
        tmp = L_NEXT(curr);
        L_DESTROY(curr);
        free(curr);
    }
    free(list);
}
