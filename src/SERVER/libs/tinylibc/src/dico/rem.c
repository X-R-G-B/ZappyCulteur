/*
** EPITECH PROJECT, 2023
** (My) Tiny Lib C
** File description:
** rem
*/

#include <stddef.h>
#include "tlcdico.h"
#include "tlcllists.h"
#include "tlcstrings.h"

dico_t *dico_rem(dico_t *dico, char const *key)
{
    dico_node_t *elem = NULL;

    if (dico == NULL) {
        return (NULL);
    }
    for (L_EACH(node, dico->interns)) {
        elem = L_DATA(node);
        if (x_strcmp(elem->key, key) != 0) {
            continue;
        }
        list_remove_ptrnode(dico->interns, node);
        return dico;
    }
    return dico;
}

dico_t *dico_rem_ptr(dico_t *dico, void *value)
{
    dico_node_t *elem = NULL;

    if (dico == NULL) {
        return (NULL);
    }
    for (L_EACH(node, dico->interns)) {
        elem = L_DATA(node);
        if (elem->value != value) {
            continue;
        }
        list_remove_ptrnode(dico->interns, node);
        return dico;
    }
    return dico;
}
