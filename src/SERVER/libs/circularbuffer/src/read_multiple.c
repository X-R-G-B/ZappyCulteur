/*
** EPITECH PROJECT, 2023
** Zappy Server
** File description:
** circular buffer lib read multiple
*/

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "tlcstrings.h"
#include "circular_buffer.h"
#include "tlcutils.h"

static char *concat(char *a, char *b)
{
    char *new = NULL;
    size_t size = 0;

    size += (a == NULL) ? 0 : x_strlen(a);
    size += (b == NULL) ? 0 : x_strlen(b);
    new = malloc(sizeof(char) * (size + 1));
    if (new == NULL) {
        return NULL;
    }
    new[0] = '\0';
    if (a != NULL) {
        strcat(new, a);
    }
    if (b != NULL) {
        strcat(new, b);
    }
    return new;
}

char *circular_buffer_read_multiple(circular_buffer_t *buffer)
{
    char *new = NULL;
    char *tmp = NULL;
    char *new_tmp = NULL;

    if (buffer == NULL) {
        return NULL;
    }
    while (circular_buffer_is_read_ready(buffer) == true) {
        tmp = circular_buffer_read(buffer);
        new_tmp = concat(new, tmp);
        if (new_tmp == NULL) {
            free_ifnotnull(tmp);
            break;
        }
    }
    return new;
}
