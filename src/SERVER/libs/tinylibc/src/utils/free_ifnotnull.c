/*
** EPITECH PROJECT, 2022
** (my) Tiny Lib C
** File description:
** free only if not null
*/

#include <stddef.h>
#include <stdlib.h>

void free_ifnotnull(void *ptr)
{
    if (ptr == NULL) {
        return;
    }
    free(ptr);
}
