/*
** EPITECH PROJECT, 2023
** zappy server ntw
** File description:
** loop
*/

#include <sys/select.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include "ntw.h"
#include "ntw_internal.h"
#include "tlcllists.h"

static void accept_new_connection(ntw_t *ntw)
{
    struct sockaddr_in addr;
    socklen_t addr_len = sizeof(addr);
    ntw_client_t *cl = NULL;
    int fd = 0;

    fd = accept(ntw->main_sock, (struct sockaddr *) &addr, &addr_len);
    if (fd < 0) {
        ntw->error = ERR_NEW_CON;
        return;
    }
    cl = ntw_client_init(fd);
    if (cl == NULL) {
        ntw->error = ERR_NEW_CON;
        shutdown(fd, SHUT_RDWR);
        close(fd);
        return;
    }
    list_append(ntw->clients, cl, (void (*)(void *)) ntw_client_destroy, NULL);
    ntw->on_new_conn(cl);
}

static void events_clients(ntw_t *ntw)
{
    ntw_client_t *cl = NULL;

    for (L_EACH(client, ntw->clients)) {
        cl = L_DATA(client);
        if (FD_ISSET(cl->fd, &ntw->except_fds)) {
            list_append(ntw->clients_to_remove, cl, NULL, NULL);
            fprintf(stderr, "ERROR: client disconnected (fd: %d)\n", cl->fd);
            continue;
        }
        if (FD_ISSET(cl->fd, &ntw->read_fds)) {
            internal_read_command(ntw, cl);
        }
        if (FD_ISSET(cl->fd, &ntw->write_fds)) {
            internal_write_command(ntw, cl);
        }
    }
}

void ntw_loop(ntw_t *ntw)
{
    if (ntw->error == ERROR) {
        return;
    }
    if (FD_ISSET(ntw->main_sock, &ntw->read_fds)) {
        accept_new_connection(ntw);
    }
    events_clients(ntw);
    internal_remove_client_clean(ntw);
}
