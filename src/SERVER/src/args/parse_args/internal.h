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

    #define NB_OPT_ARGS 6

bool parse_arg_port(const char *const arr[], args_t *args);
bool parse_arg_width(const char *const arr[], args_t *args);
bool parse_arg_height(const char *const arr[], args_t *args);
bool parse_arg_freq(const char *const arr[], args_t *args);
bool parse_arg_c_per_teams(const char *const arr[], args_t *args);
bool parse_arg_team_name(const char *const arr[], args_t *args);

#endif
