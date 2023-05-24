/*
** EPITECH PROJECT, 2023
** MyTeams
** File description:
** circular buffer lib write
*/

#include <stdlib.h>
#include <string.h>
#include "circular_buffer.h"
#include "tlcllists.h"
#include "tlcstrings.h"
#include "tlcutils.h"

static void append_circ(circular_buffer_t *buffer, const char *str)
{
    char *new = NULL;

    new = malloc(sizeof(char) *
        (x_strlen(L_DATA(buffer->buffer->end)) + x_strlen(str) + 1));
    if (new == NULL) {
        return;
    }
    new[0] = '\0';
    strcat(new, buffer->buffer->end->data);
    strcat(new, str);
    free_ifnotnull(buffer->buffer->end->data);
    buffer->buffer->end->data = new;
}

void circular_buffer_write(circular_buffer_t *buffer, const char *str)
{
    if (buffer == NULL || str == NULL) {
        return;
    }
    if (buffer->buffer->len == 0 || x_strendswith(
            L_DATA(buffer->buffer->end), buffer->end_pattern) == 1) {
        list_append(buffer->buffer, x_strdup(str), free_ifnotnull,
            (void *(*)(void *)) x_strdup);
        return;
    }
    append_circ(buffer, str);
}
