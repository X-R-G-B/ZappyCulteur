/*
** EPITECH PROJECT, 2023
** zappy server ntw internal
** File description:
** write
*/

#include <stdio.h>
#include <unistd.h>
#include "circular_buffer.h"
#include "ntw.h"
#include "ntw_internal.h"
#include "tlcllists.h"
#include "llog.h"

const char *format_err = "read error for socket fd:%d";

const char *format_close = "read closed for socket fd:%d";

const char *format_succes = "read success for socket fd:%d (message:'%s')";

void internal_read_command(ntw_t *ntw, ntw_client_t *cl)
{
    char buffer[BUFFER_SIZE + 1] = {0};
    int nbread = 0;

    if (cl == NULL || ntw == NULL) {
        return;
    }
    nbread = read(cl->fd, buffer, BUFFER_SIZE);
    if (nbread < 0) {
        perror("read");
        list_append(ntw->clients_to_remove, cl, NULL, NULL);
        llog_write_f(LOG_FILE_NETWORK, LLOG_ERROR, format_err, cl->fd);
    } else if (nbread == 0) {
        list_append(ntw->clients_to_remove, cl, NULL, NULL);
        llog_write_f(LOG_FILE_NETWORK, LLOG_INFO, format_close, cl->fd);
    } else {
        circular_buffer_write(cl->read_from_outside, buffer);
        llog_write_f(LOG_FILE_NETWORK, LLOG_TRACE, format_succes,
            cl->fd, buffer);
    }
}
