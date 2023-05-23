/*
** EPITECH PROJECT, 2023
** zappy server args
** File description:
** init
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "args.h"
#include "tlcllists.h"
#include "tlcutils.h"

static bool arg_team_name(int ac, int index, const char *const av[],
    args_t *args)
{
    int i = index + 1;

    if (args->teams_name != NULL) {
        args->is_ok = false;
        return false;
    }
    args->teams_name = list_create();
    for (; i < ac && av[i][0] != '-'; i++) {
        list_append(args->teams_name, strdup(av[i]), free_ifnotnull, NULL);
    }
    return true;
}

static bool check_arg3(int ac, int index, const char *const av[], args_t *args)
{
    if (args->is_ok == true && strcmp(av[index] + 1, "n") == 0) {
        return arg_team_name(ac, index, av, args);
    }
    if (args->is_ok == true && strcmp(av[index] + 1, "y") == 0) {
        args->height = atoi(av[index + 1]);
        if (args->height <= 0) {
            args->is_ok = false;
            fprintf(stderr, "ERROR: Invalid height: %d\n", args->height);
            return false;
        }
        return true;
    }
    return false;
}

static bool check_arg2(int ac, int index, const char *const av[], args_t *args)
{
    if (args->is_ok == true && strcmp(av[index] + 1, "c") == 0) {
        args->clients_per_teams = atoi(av[index + 1]);
        if (args->clients_per_teams <= 0) {
            args->is_ok = false;
            fprintf(stderr, "ERROR: Invalid clientsNb: %d\n",
                args->clients_per_teams);
            return false;
        }
        return true;
    }
    if (args->is_ok == true && strcmp(av[index] + 1, "f") == 0) {
        args->freq = atoi(av[index + 1]);
        if (args->freq <= 0) {
            args->is_ok = false;
            fprintf(stderr, "ERROR: Invalid freq: %d\n", args->freq);
            return false;
        }
        return true;
    }
    return check_arg3(ac, index, av, args);
}

static bool check_arg1(int ac, int index, const char *const av[], args_t *args)
{
    if (args->is_ok == true && strcmp(av[index] + 1, "p") == 0) {
        args->port = atoi(av[index + 1]);
        if (args->port < 0) {
            args->is_ok = false;
            fprintf(stderr, "ERROR: Invalid port: %d\n", args->port);
            return false;
        }
        return true;
    }
    if (args->is_ok == true && strcmp(av[index] + 1, "x") == 0) {
        args->width = atoi(av[index + 1]);
        if (args->width <= 0) {
            args->is_ok = false;
            fprintf(stderr, "ERROR: Invalid width: %d\n", args->width);
            return false;
        }
        return true;
    }
    return check_arg2(ac, index, av, args);
}

args_t *args_init(int ac, const char *const av[])
{
    args_t *args = NULL;
    int nb_args = 0;

    args = malloc(sizeof(args_t));
    if (args == NULL) {
        return NULL;
    }
    memset(args, 0, sizeof(args_t));
    args->is_ok = true;
    for (int i = 1; i < ac - 1 && args->is_ok == true; i++) {
        if (av[i][0] == '-') {
            nb_args = (check_arg1(ac, i, av, args)) ? nb_args + 1 : nb_args;
        }
    }
    if (nb_args != 6) {
        args->is_ok = false;
    }
    return args;
}
