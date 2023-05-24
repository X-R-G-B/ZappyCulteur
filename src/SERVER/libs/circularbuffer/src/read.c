/*
** EPITECH PROJECT, 2023
** MyTeams
** File description:
** circular buffer lib read
*/

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "circular_buffer.h"
#include "tlcllists.h"
#include "tlcstrings.h"

static char *copy_until_pattern(char *str, const char *pattern)
{
    char *new = NULL;
    char *tmp = NULL;

    if (str == NULL || pattern == NULL) {
        return NULL;
    }
    tmp = strstr(str, pattern);
    if (tmp == NULL) {
        return NULL;
    }
    tmp += strlen(pattern);
    new = calloc(tmp - str + 1, sizeof(char));
    if (new == NULL) {
        return NULL;
    }
    strncpy(new, str, tmp - str);
    return new;
}

static void advence_str(circular_buffer_t *buffer, char *str_new)
{
    char *new = NULL;
    char *rest = NULL;

    if (buffer == NULL || str_new == NULL || buffer->buffer->start == NULL) {
        return;
    }
    rest = ((char *) buffer->buffer->start->data) + strlen(str_new);
    if (*rest == '\0') {
        list_remove_start(buffer->buffer);
        return;
    }
    new = x_strdup(rest);
    free_ifnotnull(buffer->buffer->start->data);
    buffer->buffer->start->data = new;
}

char *circular_buffer_read(circular_buffer_t *buffer)
{
    char *new = NULL;

    if (buffer == NULL || circular_buffer_is_read_ready(buffer) == false) {
        return NULL;
    }
    new = copy_until_pattern(L_DATA(buffer->buffer->start),
        buffer->end_pattern);
    if (new == NULL) {
        return NULL;
    }
    advence_str(buffer, new);
    return new;
}
