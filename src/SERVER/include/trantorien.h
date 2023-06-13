/*
** EPITECH PROJECT, 2023
** zappy server trantorien
** File description:
** trantorian header
*/

#ifndef TRANTORIEN_H_
    #define TRANTORIEN_H_

    #include <stdbool.h>
    #include "map.h"
    #include "ntw.h"

    #define NB_PARALLEL_ACTION 11
    #define MAX_NB_TR_RESSOURCES 7
    #define MAX_FOOD_FREQ 126
    #define IS_SAME_TR_POS(tr1, tr2) (tr1->x == tr2->x && tr1->y == tr2->y)
    #define _IS_N(a) (a == NULL)
    #define IS_CMD_ARG_NL(a,b,c,d) _IS_N(a) || _IS_N(b) || _IS_N(c) || _IS_N(d)

typedef struct client_s client_t;

// compatibility with graphic trantorien direction
enum direction_e {
    NORTH = 1,
    EAST = 2,
    SOUTH = 3,
    WEST = 4,
    MAX_DIRECTION = 5
};

enum cmd_code_e {
    FORWARD = 0,
    RIGHT = 1,
    LEFT = 2,
    LOOK = 3,
    INVENTORY = 4,
    BROADCAST = 5,
    FORK = 6,
    EJECT = 7,
    TAKE = 8,
    SET = 9,
    INCANTATION = 10,
    MAX_CMD_CODE = 11
};

struct action_s {
    enum cmd_code_e code;
    union {
        char *broadcast_msg;
        enum ressource_e object;
    } param;
    int freq;
};
typedef struct action_s action_t;

struct trantorien_s {
    int id;
    char *team_name;
    int x;
    int y;
    enum direction_e direction;
    bool alive;
    int food_stack_freq;
    int level;
    const action_t *incantation;
    int ressources[MAX_NB_TR_RESSOURCES];
    action_t *actions[NB_PARALLEL_ACTION];
};
typedef struct trantorien_s trantorien_t;

trantorien_t *trantorien_init(const char *team_name, int width, int height);

void trantorien_destroy(trantorien_t *trantorien);

bool trantorien_add_act_broadcast(trantorien_t *trantorien, char *msg);
bool trantorien_add_act_take(trantorien_t *trantorien,
    enum ressource_e object);
bool trantorien_add_act_set(trantorien_t *trantorien, enum ressource_e object);
bool trantorien_add_act(trantorien_t *trantorien, enum cmd_code_e);

typedef struct zappy_s zappy_t;

void trantorien_reduce_freq(trantorien_t *trantorien, zappy_t *zappy,
    ntw_client_t *cl);


/**
** @brief Get the min case for the look around wiht substration
**
** @param x
** @param lvl
** @param size
** @return int
**/
int get_min_case_sub(int x, int lvl, int size);

/**
** @brief Get the min case for the look around wiht addition
**
** @param x
** @param lvl
** @param size
** @return int
**/
int get_min_case_add(int x, int lvl, int size);

/**
** @brief check if the trantorien can do an incantation
**
** @param trantorien
** @param map
** @param ntw
** @return true
** @return false
**/
bool check_incantation_availability(trantorien_t *trantorien, map_t *map,
    ntw_t *ntw);

/**
** @brief send the tile ressources to the client
**
** @param cl
** @param tile
** @param message_state
**/
void send_tile_ressources(ntw_client_t *cl, map_tile_t *tile,
    int message_state);

void broadcast_incantation_start(trantorien_t *ref_trantorien, zappy_t *zappy,
    ntw_client_t *cl);

/**
** @brief assign a trantorien to a client
** @param cc client
** @param trantoriens_available list of available trantoriens
**
** @note if no trantoriens are available, the trantoriens is created
**
** @return true if the trantoriens is assigned to the client false if not
**/
bool add_client_to_trantorien(client_t *cc, list_t *trantoriens_available);

#endif
