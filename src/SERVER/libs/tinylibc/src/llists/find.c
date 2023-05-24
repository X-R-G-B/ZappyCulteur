/*
** EPITECH PROJECT, 2022
** (my) Tiny Lib C
** File description:
** find something in list
*/

#include <stddef.h>
#include <stdbool.h>
#include "tlcllists.h"

node_result_t list_find_ptrdata(list_t *list, void *data)
{
    node_result_t res = {.node_index = -1, .node_ptr = NULL};
    int index = 0;

    if (list == NULL) {
        return (res);
    }
    for (L_EACH(node, list)) {
        if (L_DATA(node) == data) {
            res.node_index = index;
            res.node_ptr = node;
            return (res);
        }
        index += 1;
    }
    return (res);
}

int list_find_ptrnode(list_t *list, node_t *node_ptr)
{
    int index = 0;

    if (list == NULL) {
        return (-1);
    }
    for (L_EACH(node, list)) {
        if (node == node_ptr) {
            return (index);
        }
        index += 1;
    }
    return (-1);
}

node_result_t list_find_f(list_t *list,
    bool (is_this_result)(void *node_data, void *param), void *param)
{
    node_result_t res = {.node_index = -1, .node_ptr = NULL};
    int index = 0;

    if (list == NULL) {
        return (res);
    }
    for (L_EACH(node, list)) {
        if (is_this_result(L_DATA(node), param)) {
            res.node_ptr = node;
            res.node_index = index;
            return (res);
        }
        index += 1;
    }
    return (res);
}
