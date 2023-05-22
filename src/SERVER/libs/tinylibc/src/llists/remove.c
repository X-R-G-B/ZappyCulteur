/*
** EPITECH PROJECT, 2022
** (my) Tiny Lib C
** File description:
** remove a node
*/

#include <stddef.h>
#include <stdlib.h>
#include "tlcllists.h"

int list_remove_start(list_t *list)
{
    node_t *node = NULL;

    if (list == NULL || list->len == 0) {
        return (0);
    }
    node = list->start;
    if (list->len == 1) {
        list->start = NULL;
        list->end = NULL;
    } else {
        list->start = node->next;
    }
    L_DESTROY(node);
    free(node);
    list->len -= 1;
    return (1);
}

int list_remove_end(list_t *list)
{
    node_t *last = NULL;
    node_t *node = NULL;

    if (list == NULL || list->len == 0) {
        return (0);
    }
    node = list->end;
    if (list->len == 1) {
        list->start = NULL;
    } else {
        last = list_index(list, list->len - 2);
        list->end = last;
    }
    last->next = NULL;
    L_DESTROY(node);
    free(node);
    list->len -= 1;
    return (1);
}

static int list_remove_node_index(list_t *list, node_t *node, int index)
{
    node_t *last = NULL;

    if (index <= 0 || list->len == 1) {
        return (list_remove_start(list));
    } else if (index >= list->len - 1) {
        return (list_remove_end(list));
    }
    last = list_index(list, index - 1);
    last->next = node->next;
    L_DESTROY(node);
    free(node);
    list->len -= 1;
    return (1);
}

int list_remove_ptrnode(list_t *list, node_t *node)
{
    int index = 0;
    int res = 0;

    if (list == NULL || list->len == 0) {
        return (0);
    }
    index = list_find_ptrnode(list, node);
    if (index < 0) {
        return (0);
    }
    res = list_remove_node_index(list, node, index);
    return (res);
}

int list_remove_ptrdata(list_t *list, void *ptrdata)
{
    node_result_t node = {0};
    int res = 0;

    if (list == NULL || list->len == 0) {
        return (0);
    }
    node = list_find_ptrdata(list, ptrdata);
    if (node.node_index < 0) {
        return (0);
    }
    res = list_remove_node_index(list, node.node_ptr, node.node_index);
    return (res);
}
