/*
** EPITECH PROJECT, 2023
** MyTeams
** File description:
** circular buffer lib
*/

#ifndef CIRCULAR_BUFFER_H_
    #define CIRCULAR_BUFFER_H_

    #include <stddef.h>
    #include <stdbool.h>
    #include "tlcllists.h"

// circular buffer struct
struct circular_buffer_s {
    list_t *buffer;
    const char *end_pattern;
};
typedef struct circular_buffer_s circular_buffer_t;

// create a circular buffer
// `end_pattern` is the pattern of the end that says we can write to another
// command
circular_buffer_t *
circular_buffer_create(const char *end_pattern);

// destroy a circular buffer
void circular_buffer_destroy(circular_buffer_t *buffer);

// add a char* to the circular buffer.
// str must not be more than `circular_buffer_t.size` and contain the
// `circular_buffer_t.end_pattern`.
// if strlen(str) == `circular_buffer_t.size`
void circular_buffer_write(circular_buffer_t *buffer, const char *str);

// read a char* of size max `circular_buffer_t.size` if the end_pattern is
// present and return true.
// else return false
char *circular_buffer_read(circular_buffer_t *buffer);

// check if circular buffer is empty
bool circular_buffer_is_empty(circular_buffer_t *buffer);

// check if circular buffer is ready
bool circular_buffer_is_read_ready(circular_buffer_t *buffer);

#endif
