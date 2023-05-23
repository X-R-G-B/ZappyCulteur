/*
** EPITECH PROJECT, 2023
** zappy server global
** File description:
** header
*/

#ifndef ZAPPY_H_
    #define ZAPPY_H_

    #include <stdbool.h>
    #include "args.h"
    #include "ntw.h"

/**
** @brief Function called each time a new connection
**
** @param new_client
**/
void on_new_conn(ntw_client_t *new_client);
/**
** @brief Function called each frame
**
** @param ntw the network module
** @param args the arguments
**
** @return false if the loop should be called next time
**/
bool loop(ntw_t *ntw, args_t *args);
/**
** @brief Function to get an uniq int
**
** @return an uniq int
**/
int get_id(void);

// ---------------------------------------------------------------------------

bool update_client_not_connected(ntw_t *ntw, ntw_client_t *cl, args_t *args);
bool update_client_waiting_team_name(ntw_t *ntw, ntw_client_t *cl,
    args_t *args);
bool update_client_connected(ntw_t *ntw, ntw_client_t *cl, args_t *args);

#endif
