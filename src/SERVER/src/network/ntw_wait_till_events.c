/*
** EPITECH PROJECT, 2023
** zappy server ntw
** File description:
** wait till events
*/

#include <stdbool.h>
#include <sys/select.h>
#include <time.h>
#include <stdio.h>
#include "tlcmaths.h"
#include "circular_buffer.h"
#include "ntw.h"
#include "tlcllists.h"

static void set_ntw_fds(ntw_t *ntw)
{
    ntw_client_t *cl = NULL;

    FD_ZERO(&ntw->write_fds);
    FD_ZERO(&ntw->read_fds);
    FD_ZERO(&ntw->except_fds);
    FD_SET(ntw->main_sock, &ntw->read_fds);
    ntw->max_fd = ntw->main_sock;
    for (L_EACH(client, ntw->clients)) {
        cl = L_DATA(client);
        if (circular_buffer_is_read_ready(cl->write_to_outside) == true) {
            FD_SET(cl->fd, &ntw->write_fds);
        } else {
            FD_SET(cl->fd, &ntw->read_fds);
        }
        ntw->max_fd = x_max(ntw->max_fd, cl->fd);
    }
}

static bool wait_ntw_events(ntw_t *ntw, time_t seconds_timeout,
    suseconds_t microseconds_timeout)
{
    int status = 0;
    struct timeval timeout = {
        .tv_sec = seconds_timeout,
        .tv_usec = microseconds_timeout
    };

    status = select(ntw->max_fd + 1, &ntw->read_fds, &ntw->write_fds,
        &ntw->except_fds, &timeout);
    if (status == -1) {
        perror("select");
        return false;
    } else if (status == 0) {
        return false;
    } else {
        return true;
    }
}

bool ntw_wait_till_events(ntw_t *ntw, time_t seconds_timeout,
    suseconds_t microseconds_timeout)
{
    bool status = false;

    set_ntw_fds(ntw);
    status = wait_ntw_events(ntw, seconds_timeout, microseconds_timeout);
    return status;
}
