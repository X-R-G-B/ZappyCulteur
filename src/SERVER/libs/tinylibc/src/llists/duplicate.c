/*
** EPITECH PROJECT, 2022
** (my) Tiny Lib C
** File description:
** duplicate a list
*/

#include <stddef.h>
#include "tlcllists.h"

list_t *list_duplicate(list_t *list)
{
    list_t *new = NULL;
    void *tmp = NULL;

    if (list == NULL) {
        return (NULL);
    }
    new = list_create();
    if (new == NULL) {
        return (NULL);
    }
    for (L_EACH(node, list)) {
        if (node->copy != NULL) {
            tmp = L_COPY(node);
            list_append(new, tmp, node->destroy, node->copy);
        }
    }
    return (new);
}
