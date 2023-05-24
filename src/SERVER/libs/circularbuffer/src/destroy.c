/*
** EPITECH PROJECT, 2023
** MyTeams
** File description:
** circular buffer lib destroy
*/

#include <stdlib.h>
#include "circular_buffer.h"
#include "tlcllists.h"

void circular_buffer_destroy(circular_buffer_t *buffer)
{
    if (buffer == NULL) {
        return;
    }
    if (buffer->buffer != NULL) {
        list_delete(buffer->buffer);
    }
    free(buffer);
}
