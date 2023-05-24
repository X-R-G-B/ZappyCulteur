/*
** EPITECH PROJECT, 2023
** MyTeams
** File description:
** check if buffer is empty
*/

#include <stdbool.h>
#include "tlcllists.h"
#include "tlcstrings.h"
#include "circular_buffer.h"

bool circular_buffer_is_empty(circular_buffer_t *buffer)
{
    if (buffer == NULL) {
        return true;
    }
    if (buffer->buffer->len == 0) {
        return true;
    }
    return false;
}

bool circular_buffer_is_read_ready(circular_buffer_t *buffer)
{
    if (buffer == NULL || circular_buffer_is_empty(buffer) == true) {
        return false;
    }
    if (x_strstr(L_DATA(buffer->buffer->start),
            buffer->end_pattern) != NULL) {
        return true;
    }
    return false;
}
