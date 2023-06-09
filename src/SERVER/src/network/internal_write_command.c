/*
** EPITECH PROJECT, 2023
** zappy server ntw internal
** File description:
** write
*/

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include "circular_buffer.h"
#include "ntw.h"
#include "ntw_internal.h"
#include "tlcllists.h"
#include "llog.h"

void internal_write_command(ntw_t *ntw, ntw_client_t *cl)
{
    char *to_write = NULL;
    size_t to_write_size = 0;
    size_t nbwrite = 0;

    to_write = circular_buffer_read_multiple(cl->write_to_outside);
    if (to_write == NULL) {
        return;
    }
    to_write_size = strlen(to_write);
    nbwrite = write(cl->fd, to_write, to_write_size);
    if (nbwrite == (size_t) -1) {
        perror("write");
        list_append(ntw->clients_to_remove, cl, NULL, NULL);
        llog_write_f(LOG_FILE_NETWORK, LLOG_ERROR,
            "write error for socket fd:%d (message:'%s')", cl->fd, to_write);
    } else {
        llog_write_f(LOG_FILE_NETWORK, LLOG_TRACE,
            "write success for socket fd:%d (message:'%s')", cl->fd, to_write);
    }
    free(to_write);
}
