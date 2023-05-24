/*
** EPITECH PROJECT, 2023
** (My) Tiny Lib C
** File description:
** create
*/

#include <stddef.h>
#include <stdlib.h>
#include "tlcdico.h"
#include "tlcllists.h"

dico_t *dico_create(void)
{
    dico_t *dico = malloc(sizeof(dico_t));

    if (dico == NULL) {
        return (NULL);
    }
    dico->interns = list_create();
    if (dico->interns == NULL) {
        free(dico);
        return (NULL);
    }
    return (dico);
}
