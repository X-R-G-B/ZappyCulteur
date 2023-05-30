/*
** EPITECH PROJECT, 2023
** (My) Tiny Lib C
** File description:
** get
*/

#include "tlcdico.h"
#include "tlcllists.h"
#include "tlcstrings.h"

void *dico_get_value(dico_t *dico, char const *key)
{
    dico_node_t *elem = NULL;

    for (L_EACH(node, dico->interns)) {
        elem = L_DATA(node);
        if (x_strcmp(elem->key, key) != 0) {
            continue;
        }
        return elem->value;
    }
    return NULL;
}

dico_node_t *dico_get_elem(dico_t *dico, char const *key)
{
    dico_node_t *elem = NULL;

    for (L_EACH(node, dico->interns)) {
        elem = L_DATA(node);
        if (x_strcmp(elem->key, key) != 0) {
            continue;
        }
        return elem;
    }
    return NULL;
}

dico_node_t *dico_get_ptr(dico_t *dico, void *value)
{
    dico_node_t *elem = NULL;

    for (L_EACH(node, dico->interns)) {
        elem = L_DATA(node);
        if (elem->value != value) {
            continue;
        }
        return elem;
    }
    return NULL;
}
