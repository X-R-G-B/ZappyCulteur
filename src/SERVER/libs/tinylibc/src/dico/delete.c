/*
** EPITECH PROJECT, 2023
** (My) Tiny Lib C
** File description:
** delete
*/

#include <stddef.h>
#include <stdlib.h>
#include "tlcdico.h"
#include "tlcllists.h"

void dico_detroy_ptr(void *dico_node)
{
    dico_node_t *dico = dico_node;

    if (dico_node == NULL) {
        return;
    }
    if (dico->destroy != NULL) {
        dico->destroy(dico->value);
    }
    free(dico);
}

void dico_destroy(dico_t *dico)
{
    if (dico == NULL) {
        return;
    }
    list_delete(dico->interns);
    free(dico);
}
