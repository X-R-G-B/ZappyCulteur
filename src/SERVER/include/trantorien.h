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

    #define NB_PARALLEL_ACTION 10

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
    const char *team_name;
    int x;
    int y;
    enum direction_e direction;
    bool alive;
    int level;
    int ressources[MAX_NB_RESOURCES];
    action_t *actions[NB_PARALLEL_ACTION];
};
typedef struct trantorien_s trantorien_t;

trantorien_t *trantorien_init(const char *team_name, int id,
    int width, int height);

void trantorien_destroy(trantorien_t *trantorien);

bool trantorien_add_act_broadcast(trantorien_t *trantorien, char *msg);
bool trantorien_add_act_take(trantorien_t *trantorien,
    enum ressource_e object);
bool trantorien_add_act_set(trantorien_t *trantorien, enum ressource_e object);
bool trantorien_add_act(trantorien_t *trantorien, enum cmd_code_e);

#endif