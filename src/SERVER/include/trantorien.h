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

// compatibility with graphic trantorien direction
enum direction_e {
    NORTH = 1,
    EAST = 2,
    SOUTH = 3,
    WEST = 4,
    MAX_DIRECTION = 5
};

struct trantorien_s {
    int id;
    const char *team_name;
    int x;
    int y;
    enum direction_e direction;
    bool alive;
    int level;
    int ressources[MAX_NB_RESOURCES];
};
typedef struct trantorien_s trantorien_t;

trantorien_t *trantorien_init(const char *team_name, int id,
    int width, int height);

void trantorien_destroy(trantorien_t *trantorien);

#endif
