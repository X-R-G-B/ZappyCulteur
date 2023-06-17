/*
** EPITECH PROJECT, 2023
** zappy server ntw
** File description:
** init
*/

#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <ifaddrs.h>
#include <netdb.h>
#include "ntw.h"

static size_t socklen = sizeof(struct sockaddr_in);

static void print_info_socket(struct sockaddr_in addr)
{
    struct ifaddrs *ifaddr = NULL;
    char host[512] = {0};

    printf("INFO: listening on port: %d\n", ntohs(addr.sin_port));
    if (getifaddrs(&ifaddr) == -1) {
        perror("getifaddrs");
        return;
    }
    for (struct ifaddrs *ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
        if (ifa->ifa_addr == NULL) {
            continue;
        }
        if (ifa->ifa_addr->sa_family == AF_INET && getnameinfo(ifa->ifa_addr,
                socklen, host, 511, NULL, 0, NI_NUMERICHOST) == 0) {
            printf("INFO: available at host: %s\n", host);
        }
    }
    freeifaddrs(ifaddr);
}

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
    if (bind(fd, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
        perror("bind");
        return (-1);
    }
    if (listen(fd, max_connected_clients) < 0) {
        perror("listen");
        return (-1);
    }
    print_info_socket(addr);
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

ntw_t *ntw_init(int port, int max_connected_clients,
    void (*on_new_conn)(ntw_client_t *new_client))
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
    ntw->on_new_conn = on_new_conn;
    return ntw;
}
