/*
** EPITECH PROJECT, 2023
** zappy server args
** File description:
** init
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "llog.h"
#include "args.h"
#include "parse_args/internal.h"
#include "tlcstrings.h"

static const char *ok_flags = "111111";
static const char ok_flag = '1';

static const char *const arr[NB_OPT_ARGS] = {
    ARG_PORT,
    ARG_WIDTH,
    ARG_HEIGHT,
    ARG_FREQ,
    ARG_C_PER_TEAMS,
    ARG_TEAM_NAME,
    ARG_C_MAX,
    ARG_HELP
};

static bool (*funcs[NB_OPT_ARGS])(const char *const arr[], args_t *args) = {
    parse_arg_port,
    parse_arg_width,
    parse_arg_height,
    parse_arg_freq,
    parse_arg_c_per_teams,
    parse_arg_team_name,
    parse_arg_c_max,
    help_flag
};

static bool check_exec_parse(const char *const av[], args_t *args,
    char checklist[NB_OPT_ARGS])
{
    bool is_ok = false;

    for (int j = 0; j < NB_OPT_ARGS; j++) {
        if (strcmp(av[0], arr[j]) == 0) {
            is_ok = funcs[j](av, args);
            checklist[j] = ok_flag;
            llog_write_fd(STDERR_FILENO, LLOG_DEBUG, "parsing cmd:%s", av[0]);
            return is_ok;
        }
    }
    return is_ok;
}

static bool parse_args(int ac, const char *const av[], args_t *args)
{
    bool is_an_opt = true;
    char check_all[NB_OPT_ARGS + 1] = {0};

    for (int i = 1; i < ac && args->is_ok == true; i += 1) {
        if (av[i][0] != '-') {
            continue;
        }
        is_an_opt = check_exec_parse(av + i, args, check_all);
        if (is_an_opt == false) {
            args->is_ok = false;
        }
    }
    check_all[ARG_MANDATORY_NB] = '\0';
    if (x_strcmp(check_all, ok_flags) != 0) {
        args->is_ok = false;
    }
    return args->is_ok;
}

static void set_default_args(args_t *args)
{
    args->port = 4242;
    args->width = 10;
    args->height = 10;
    args->freq = 100;
    args->clients_per_teams = 1;
    args->teams_name = list_create();
    list_append(args->teams_name, "Team1", NULL, NULL);
    printf("INFO: No args, setting default args\n");
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
    args->client_max = DEFAULT_ARG_C_MAX;
    args->is_ok = true;
    if (ac == 1) {
        set_default_args(args);
    } else {
        parse_args(ac, av, args);
    }
    return args;
}
