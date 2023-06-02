/*
** EPITECH PROJECT, 2023
** zappy server
** File description:
** network include
*/

#ifndef NTW_H_
    #define NTW_H_

    #include <stdbool.h>
    #include <sys/select.h>
    #include <time.h>
    #include "tlcllists.h"
    #include "circular_buffer.h"

enum ntw_error_e {
    OK = 0,
    TIMEOUT,
    ERROR,
    ERR_NEW_CON,
};

struct ntw_client_s {
    int fd;
    circular_buffer_t *read_from_outside;
    circular_buffer_t *write_to_outside;
    void *data;
    void (*on_delete)(void *data);
};
typedef struct ntw_client_s ntw_client_t;

/**
** @brief Initialize a new client
**
** @param fd the socket descriptor
**
** @return the new client
**/
ntw_client_t *ntw_client_init(int fd);

/**
** @brief Destroy a client
**
** @param client the client
**/
void ntw_client_destroy(ntw_client_t *client);

struct ntw_s {
    int main_sock;
    list_t *clients;
    list_t *clients_to_remove;
    fd_set write_fds;
    fd_set read_fds;
    fd_set except_fds;
    int max_fd;
    enum ntw_error_e error;
    void (*on_new_conn)(ntw_client_t *new_client);
};
typedef struct ntw_s ntw_t;

/**
** @brief Initialize the network module
**
** @param port the port to listen
** @param max_connected_clients the maximum number of clients
** @param on_new_conn the callback function when new client connect
**
** @return the network module
**/
ntw_t *ntw_init(int port, int max_connected_clients,
    void (*on_new_conn)(ntw_client_t *new_client));

/**
** @brief Destroy the network module
**
** @param ntw the network module
**/
void ntw_destroy(ntw_t *ntw);

/**
** @brief Wait for events (ex: write to socket client)
**
** @param ntw the network module
** @param seconds_timeout the number of maximum seconds to wait for events
**
** @return true if there are events (false if there is timeout). For better
** result, check the enum `ntw_t.error` for more information
**/
bool ntw_wait_till_events(ntw_t *ntw, time_t seconds_timeout,
    suseconds_t microseconds_timeout);

/**
** @brief Functon that update all its internal datas (better to call this
** after ntw_wait_till_events)
**
** @param ntw the network module
**/
void ntw_loop(ntw_t *ntw);

#endif
