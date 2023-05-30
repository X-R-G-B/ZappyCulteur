/*
** EPITECH PROJECT, 2023
** zappy server ntw
** File description:
** client destroy
*/

#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include "circular_buffer.h"
#include "ntw.h"

void ntw_client_destroy(ntw_client_t *cl)
{
    if (cl == NULL) {
        return;
    }
    if (cl->fd > 0) {
        shutdown(cl->fd, SHUT_RDWR);
        close(cl->fd);
        cl->fd = -1;
    }
    circular_buffer_destroy(cl->read_from_outside);
    cl->read_from_outside = NULL;
    circular_buffer_destroy(cl->write_to_outside);
    cl->write_to_outside = NULL;
    free(cl);
}
