/*
** EPITECH PROJECT, 2022
** (my) Tiny Lib C
** File description:
** append a data to a list
*/

#include <stddef.h>
#include <stdlib.h>
#include "tlcllists.h"

list_t *list_append(list_t *list, void *data, void (*destroy)(void *data),
    void *(*copy)(void *data))
{
    node_t *new_node = NULL;

    if (list == NULL) {
        return (NULL);
    }
    new_node = node_create(data, destroy, copy);
    if (new_node == NULL) {
        return (list);
    }
    if (list->len != 0) {
        list->end->next = new_node;
    } else {
        list->start = new_node;
    }
    list->len += 1;
    list->end = new_node;
    return (list);
}
