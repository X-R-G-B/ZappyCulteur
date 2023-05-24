/*
** EPITECH PROJECT, 2023
** (My) Tiny Lib C
** File description:
** pop
*/

#include "tlcdico.h"
#include "tlcllists.h"
#include "tlcstrings.h"
#include <stdlib.h>

void *dico_pop_value(dico_t *dico, char const *key)
{
    dico_node_t *elem = NULL;
    node_t *lnode = NULL;
    void *value = NULL;

    for (L_EACH(node, dico->interns)) {
        elem = L_DATA(node);
        if (x_strcmp(elem->key, key) != 0) {
            lnode = node;
            continue;
        }
        lnode = node->next;
        value = elem->value;
        free(node);
        free(elem);
        node = lnode;
        break;
    }
    return value;
}

dico_node_t *dico_pop_elem(dico_t *dico, char const *key)
{
    dico_node_t *elem = NULL;
    node_t *lnode = NULL;
    _Bool found = false;

    for (L_EACH(node, dico->interns)) {
        elem = L_DATA(node);
        if (x_strcmp(elem->key, key) != 0) {
            lnode = node;
            continue;
        }
        lnode = node->next;
        free(node);
        node = lnode;
        found = true;
        break;
    }
    return (found ? elem : NULL);
}
