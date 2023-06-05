/*
** EPITECH PROJECT, 2023
** zappy server args
** File description:
** init
*/

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "args.h"
#include "parse_args/internal.h"

static const char *const arr[NB_OPT_ARGS] = {
    "-p",
    "-x",
    "-y",
    "-f",
    "-c",
    "-n"
};

static bool (*funcs[NB_OPT_ARGS])(const char *const arr[], args_t *args) = {
    parse_arg_port,
    parse_arg_width,
    parse_arg_height,
    parse_arg_freq,
    parse_arg_c_per_teams,
    parse_arg_team_name
};

static bool check_exec_parse(const char *const av[], args_t *args)
{
    for (int j = 0; j < NB_OPT_ARGS; j++) {
        if (strcmp(av[0], arr[j]) == 0) {
            return funcs[j](av, args);
        }
    }
    return false;
}

static bool parse_args(int ac, const char *const av[], args_t *args)
{
    bool is_an_opt = true;
    int nb = 0;

    for (int i = 1; i < ac && args->is_ok == true; i += 1) {
        if (av[i][0] != '-') {
            continue;
        }
        is_an_opt = check_exec_parse(av + i, args);
        if (is_an_opt == false) {
            args->is_ok = false;
        } else {
            nb++;
        }
    }
    if (nb != 6) {
        args->is_ok = false;
    }
    return args->is_ok;
}

args_t *args_init(int ac, const char *const av[])
{
    args_t *args = NULL;

    args = malloc(sizeof(args_t));
    if (args == NULL) {
        return NULL;
    }
    memset(args, 0, sizeof(args_t));
    args->port = -1;
    args->is_ok = true;
    parse_args(ac, av, args);
    return args;
}
