/*
** EPITECH PROJECT, 2022
** (my) Tiny Lib C
** File description:
** get node at index
*/

#include <stddef.h>
#include "tlcllists.h"

static node_t *list_index_search(list_t *list, int index)
{
    int curr = 0;

    for (L_EACH(node, list)) {
        if (index == curr) {
            return (node);
        }
        curr += 1;
    }
    return (NULL);
}

node_t *list_index(list_t *list, int index)
{
    if (list == NULL) {
        return (NULL);
    }
    if (index >= list->len) {
        return (L_LAST(list));
    } else if (index <= 0) {
        return (L_FIRST(list));
    } else {
        return (list_index_search(list, index));
    }
}
