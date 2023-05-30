/*
** EPITECH PROJECT, 2023
** zappy server graphic cmd
** File description:
** msz
*/

#include <stdlib.h>
#include "circular_buffer.h"
#include "tlcstdlibs.h"
#include "zappy.h"
#include "internal.h"

static void send_size(args_t *args, ntw_client_t *cl)
{
    char *size_to_str = NULL;

    size_to_str = x_itoa(args->width);
    if (size_to_str == NULL) {
        return;
    }
    circular_buffer_write(cl->write_to_outside, size_to_str);
    free(size_to_str);
    circular_buffer_write(cl->write_to_outside, " ");
    size_to_str = x_itoa(args->height);
    if (size_to_str == NULL) {
        return;
    }
    circular_buffer_write(cl->write_to_outside, size_to_str);
    free(size_to_str);
    circular_buffer_write(cl->write_to_outside, "\n");
}

bool cmd_msz(__attribute__((unused)) ntw_t *ntw, ntw_client_t *cl,
    args_t *args, __attribute__((unused)) char **cmd_split)
{
    circular_buffer_write(cl->write_to_outside, "msz ");
    send_size(args, cl);
    return true;
}