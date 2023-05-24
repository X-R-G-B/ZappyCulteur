/*
** EPITECH PROJECT, 2023
** (My) Tiny Lib C
** File description:
** add
*/

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <tlcstrings.h>
#include "tlcdico.h"
#include "tlcllists.h"

void dico_detroy_ptr(void *dico_node);

dico_t *dico_add(dico_t *dico, char const *key, void *value,
    void (*destroy)(void *value))
{
    dico_node_t *elem = NULL;

    if (dico == NULL) {
        return (NULL);
    }
    elem = malloc(sizeof(dico_node_t));
    if (elem == NULL) {
        return (NULL);
    }
    elem->destroy = destroy;
    memset(elem->key, 0, sizeof(elem->key));
    x_strncpy(elem->key, key, 255);
    elem->value = value;
    return (dico_add_elem(dico, elem));
}

dico_t *dico_add_elem(dico_t *dico, dico_node_t *elem)
{
    if (dico == NULL) {
        return (NULL);
    }
    if (elem == NULL) {
        return (NULL);
    }
    dico->interns = list_append(dico->interns, elem, dico_detroy_ptr, NULL);
    return (dico);
}
