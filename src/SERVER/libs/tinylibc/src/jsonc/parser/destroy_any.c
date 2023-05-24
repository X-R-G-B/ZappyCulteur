/*
** EPITECH PROJECT, 2022
** json parser
** File description:
** get destroy
*/

#include <stdlib.h>
#include "tlcdico.h"
#include "tlcjson.h"
#include "tlcllists.h"
#include "tlcutils.h"

void destroy_any(void *data)
{
    any_t *any = data;

    if (any == NULL) {
        return;
    }
    switch (any->type) {
        case STR:
            free_ifnotnull(any->value.str);
            break;
        case DICT:
            dico_destroy(any->value.dict);
            break;
        case ARRAY:
            list_delete(any->value.array);
            break;
        default:
            break;
    }
    free(any);
}
