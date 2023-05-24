/*
** EPITECH PROJECT, 2022
** (my) Tiny Lib C
** File description:
** insert a node at an index
*/

#include <stddef.h>
#include "tlcllists.h"

list_t *list_insert_end(list_t *list, node_t *node)
{
    if (list == NULL || node == NULL) {
        return ((node == NULL) ? list : NULL);
    }
    node->next = NULL;
    if (list->len == 0) {
        list->start = node;
        list->end = node;
    } else {
        list->end->next = node;
        list->end = node;
    }
    list->len += 1;
    return (list);
}

list_t *list_insert_start(list_t *list, node_t *node)
{
    if (list == NULL || node == NULL) {
        return ((node == NULL) ? list : NULL);
    }
    node->next = list->start;
    list->start = node;
    if (list->len == 0) {
        list->end = node;
    }
    list->len += 1;
    return (list);
}

static list_t *list_insert_at(list_t *list, node_t *node, int index)
{
    node_t *last = NULL;

    last = list_index(list, index - 1);
    if (last == NULL) {
        return (list);
    }
    node->next = last->next;
    last->next = node;
    list->len += 1;
    return (list);
}

list_t *list_insert(list_t *list, node_t *node, int index)
{
    if (list == NULL || node == NULL) {
        return ((node == NULL) ? list : NULL);
    }
    if (index >= list->len) {
        return (list_insert_end(list, node));
    } else if (index <= 0) {
        return (list_insert_start(list, node));
    } else {
        return (list_insert_at(list, node, index));
    }
}
