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
    #include "trantorien.h"

    #define LVL_MAX 8

struct zappy_s {
    ntw_t *ntw;
    map_t *map;
    args_t *args;
};
typedef struct zappy_s zappy_t;

/**
** @brief Initialize a zappy
**
** @param args the arguments
**
** @return the initialized zappy
**/
zappy_t *zappy_init(args_t *args);

/**
** @brief Destroy a zappy
**
** @param zappy the zappy
**/
void zappy_destroy(zappy_t *zappy);

/**
** @brief Find a trantorien by id
**
** @param zappy the zappy
** @param id the id
**
** @return the trantorien
**/
trantorien_t *zappy_trantorien_find_by_id(zappy_t *zappy, int id);

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
