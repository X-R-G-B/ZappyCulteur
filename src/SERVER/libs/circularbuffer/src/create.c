/*
** EPITECH PROJECT, 2023
** MyTeams
** File description:
** circular buffer lib create
*/

#include <stdlib.h>
#include <string.h>
#include "circular_buffer.h"
#include "tlcllists.h"

circular_buffer_t *circular_buffer_create(const char *end_pattern)
{
    circular_buffer_t *buffer = NULL;

    if (end_pattern == NULL) {
        return (NULL);
    }
    buffer = malloc(sizeof(circular_buffer_t));
    if (buffer == NULL) {
        return (NULL);
    }
    memset(buffer, 0, sizeof(circular_buffer_t));
    buffer->buffer = list_create();
    if (buffer->buffer == NULL) {
        circular_buffer_destroy(buffer);
        return NULL;
    }
    buffer->end_pattern = end_pattern;
    return (buffer);
}
