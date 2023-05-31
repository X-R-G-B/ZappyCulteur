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
    #include "map.h"
    #include "ntw.h"

struct zappy_s {
    ntw_t *ntw;
    map_t *map;
    args_t *args;
};
typedef struct zappy_s zappy_t;

zappy_t *zappy_init(args_t *args);

void zappy_destroy(zappy_t *zappy);

/**
** @brief Function called each time a new connection
**
** @param new_client
**/
void on_new_conn(ntw_client_t *new_client);
/**
** @brief Function called each frame
**
** @param zappy the zappy
**
** @return false if the loop should be called next time
**/
bool loop(zappy_t *zappy);
/**
** @brief Function to get an uniq int
**
** @return an uniq int
**/
int get_id(void);

// ---------------------------------------------------------------------------

// Update in states

bool update_client_not_connected(zappy_t *zappy, ntw_client_t *cl);
bool update_client_waiting_team_name(zappy_t *zappy, ntw_client_t *cl);
bool update_client_connected(zappy_t *zappy, ntw_client_t *cl);

// update by types in state connected

bool update_ai_cmd(zappy_t *zappy, ntw_client_t *cl);
bool update_graphic_cmd(zappy_t *zappy, ntw_client_t *cl);

#endif
