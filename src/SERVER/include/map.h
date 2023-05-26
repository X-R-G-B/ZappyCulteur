/*
** EPITECH PROJECT, 2023
** zappy server map
** File description:
** map header
*/

#ifndef MAP_H_
    #define MAP_H_

    #include "tlcllists.h"

    #define MAX_NB_RESOURCES 7

enum ressource_e {
    FOOD = 0,
    LINEMATE = 1,
    DERAUMERE = 2,
    SIBUR = 3,
    MENDIANE = 4,
    PHIRAS = 5,
    THYSTAME = 6,
    MAX_RESSOURCE = MAX_NB_RESOURCES,
};

struct map_tile_s {
    list_t *trantors;
    int nb_food;
    int nb_linemate;
    int nb_deraumere;
    int nb_sibur;
    int nb_mendiane;
    int nb_phiras;
    int nb_thystame;
};
typedef struct map_tile_s map_tile_t;

struct map_s {
    int height;
    int width;
    map_tile_t *tiles;
};
typedef struct map_s map_t;

/**
** @brief Initialize a map
**
** @param width the map width
** @param height the map height
**
** @return the initialized map
**/
map_t *map_init(int width, int height);

/**
** @brief Destroy a map
**
** @param map the map
**/
void map_destroy(map_t *map);

/**
** @brief Add ressources
**
** @param map the map
**/
void map_add_ressources(map_t *map);

/**
** @brief index i to x y
**
** @param map the map
** @param i the index
** @param x x
** @param y y
**/
void map_index_i_to_x_y(map_t *map, int i, int *x, int *y);

/**
** @brief index x y to i
**
** @param map the map
** @param x x
** @param y y
** @param i the index
**/
void map_index_x_y_to_i(map_t *map, int x, int y, int *i);

#endif
