/*
** EPITECH PROJECT, 2023
** zappy server global
** File description:
** header
*/

#ifndef ZAPPY_H_
    #define ZAPPY_H_

    #include <stdbool.h>
    #include <stddef.h>
    #include "args.h"
    #include "map.h"
    #include "ntw.h"
    #include "trantorien.h"

    #define LVL_MAX 8

    #define NB_FREQ_BEFORE_RESOURCE 20

extern const int level_ressources[LVL_MAX - 1][PLAYER];

struct zappy_s {
    ntw_t *ntw;
    map_t *map;
    args_t *args;
    size_t cur_tick;
    size_t before_add_resources;
    list_t *trantoriens_available;
    bool is_end;
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
** @param new_freq if it is a new freq time
**
** @return false if the loop should be called next time
**/
bool loop(zappy_t *zappy, bool new_freq);
/**
** @brief Function to get an uniq int
**
** @return an uniq int
**/
int get_id(void);
/**
** @brief Broadcast a message to all graphic
**
** @param ntw the ntw
** @param msg the message
**
** @return true if broadcast
**/
bool broadcast_graphic(ntw_t *ntw, const char *msg);

/**
** @brief Create a list of trantorien considered as egg
**
** @param args the cmd arguments
**
** @return the list of trantorien_t
**/
list_t *zappy_create_initial_egg(args_t *args);

/**
** @brief Check if the game is ended
** @param zappy
** @return true if the game is ended
**/
bool check_end(zappy_t *zappy, bool is_end);

/**
** @brief Connect after graphic send events
**
** @param cc client afiliated to ntw_client
** @param cl ntw client
** @param zappy the module
**/
void connect_graphic_client(client_t *cc, ntw_client_t *cl, zappy_t *zappy);

#endif
