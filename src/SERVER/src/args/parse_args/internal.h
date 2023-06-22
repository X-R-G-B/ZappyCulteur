/*
** EPITECH PROJECT, 2023
** zappy server args intenal
** File description:
** header
*/

#ifndef ARGS_INTERNAL_H_
    #define ARGS_INTERNAL_H_

    #include <stdbool.h>
    #include "args.h"

    #define NB_OPT_ARGS 7

    #define ARG_PORT "-p"
    #define ARG_WIDTH "-x"
    #define ARG_HEIGHT "-y"
    #define ARG_FREQ "-f"
    #define ARG_C_PER_TEAMS "-c"
    #define ARG_TEAM_NAME "-n"
    #define ARG_C_MAX "-m"

    #define DEFAULT_ARG_C_MAX 150

    #define OK_IINT "123456789"

bool parse_arg_port(const char *const arr[], args_t *args);
bool parse_arg_width(const char *const arr[], args_t *args);
bool parse_arg_height(const char *const arr[], args_t *args);
bool parse_arg_freq(const char *const arr[], args_t *args);
bool parse_arg_c_per_teams(const char *const arr[], args_t *args);
bool parse_arg_team_name(const char *const arr[], args_t *args);
bool parse_arg_c_max(const char *const arr[], args_t *args);

#endif
