/*
** EPITECH PROJECT, 2023
** zappy server ntw
** File description:
** internal header
*/

#ifndef NTW_INTERNAL_H_
    #define NTW_INTERNAL_H_

    #include "ntw.h"

    #define BUFFER_SIZE 1024

/**
** @brief Remove clients stored in clients_to_remove from the list of clients
**
** @param ntw the network module
**/
void internal_remove_client_clean(ntw_t *ntw);
/**
** @brief Read a command from the client and stored it in read_from_outside
**
** @param ntw the network module
** @param cl the client
**/
void internal_read_command(ntw_t *ntw, ntw_client_t *cl);
/**
** @brief Write a command to the client (command was stored in
** write_to_outside)
**
** @param ntw the network module
** @param cl the client
**/
void internal_write_command(ntw_t *ntw, ntw_client_t *cl);

#endif
