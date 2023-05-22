/*
** EPITECH PROJECT, 2023
** zappy server ntw
** File description:
** init
*/

#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include "ntw.h"

static int create_socket(int port, int max_connected_clients)
{
    int fd = 0;
    struct sockaddr_in addr = {.sin_family = AF_INET, .sin_port = htons(port)};

    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        perror("socket");
        return (-1);
    }
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("bind");
        return (-1);
    }
    if (listen(fd, max_connected_clients) < 0) {
        perror("listen");
        return (-1);
    }
    return (fd);
}

static bool init_lists(ntw_t *ntw)
{
    ntw->clients = list_create();
    if (ntw->clients == NULL) {
        return (false);
    }
    ntw->clients_to_remove = list_create();
    if (ntw->clients_to_remove == NULL) {
        return (false);
    }
    return (true);
}

ntw_t *ntw_init(int port, int max_connected_clients)
{
    ntw_t *ntw = NULL;
    int fd = 0;

    fd = create_socket(port, max_connected_clients);
    if (fd < 0) {
        return (NULL);
    }
    ntw = malloc(sizeof(ntw_t));
    if (ntw == NULL) {
        close(fd);
    }
    memset(ntw, 0, sizeof(ntw_t));
    ntw->main_sock = fd;
    if (init_lists(ntw) == false) {
        ntw_destroy(ntw);
        return NULL;
    }
    return ntw;
}
