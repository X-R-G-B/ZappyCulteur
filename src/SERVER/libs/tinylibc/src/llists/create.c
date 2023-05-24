/*
** EPITECH PROJECT, 2022
** (my) Tiny Lib C
** File description:
** create a list_t
*/

#include <stddef.h>
#include <stdlib.h>
#include "tlcllists.h"

list_t *list_create(void)
{
    list_t *new = NULL;

    new = malloc(sizeof(list_t));
    if (new == NULL) {
        return (NULL);
    }
    new->start = NULL;
    new->end = NULL;
    new->len = 0;
    return (new);
}

node_t *node_create(void *data, void (*destroy)(void *data),
    void *(*copy)(void *data))
{
    node_t *new = NULL;

    new = malloc(sizeof(node_t));
    if (new == NULL) {
        return (NULL);
    }
    new->data = data;
    new->destroy = destroy;
    new->copy = copy;
    new->next = NULL;
    return (new);
}
