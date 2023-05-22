/*
** EPITECH PROJECT, 2023
** zappy server ntw
** File description:
** destroy
*/

#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include "tlcllists.h"
#include "ntw.h"

void ntw_destroy(ntw_t *ntw)
{
    list_delete(ntw->clients);
    ntw->clients = NULL;
    list_delete(ntw->clients_to_remove);
    ntw->clients_to_remove = NULL;
    if (ntw->main_sock > 0) {
        if (shutdown(ntw->main_sock, SHUT_RDWR) < 0) {
            perror("shutdown");
        }
        close(ntw->main_sock);
    }
}
