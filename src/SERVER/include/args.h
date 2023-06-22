/*
** EPITECH PROJECT, 2023
** zappy server args
** File description:
** args header
*/

#ifndef ARGS_H_
    #define ARGS_H_

    #include <stdbool.h>
    #include <stddef.h>
    #include "tlcllists.h"

    #define ARG_MANDATORY_NB 6

struct args_s {
    int port;
    int width;
    int height;
    list_t *teams_name;
    int clients_per_teams;
    int freq;
    int client_max;
    bool is_ok;
    bool is_help;
};
typedef struct args_s args_t;

/**
** @brief Initialize args
**
** @param ac number of arguments
** @param av arguments
**/
args_t *args_init(int ac, const char *const av[]);

/**
** @brief Destroy args
**
** @param args args
**/
void args_destroy(args_t *args);

/**
** @brief Print args
**
** @param args args
**/
void args_debug(args_t *args);

#endif
