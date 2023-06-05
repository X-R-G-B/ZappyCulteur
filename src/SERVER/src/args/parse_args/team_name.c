/*
** EPITECH PROJECT, 2023
** zappy server args parse
** File description:
** port
*/

#include <stdbool.h>
#include <stdlib.h>
#include "tlcllists.h"
#include "tlcstdlibs.h"
#include "tlcstrings.h"
#include "args.h"
#include "internal.h"

static void add_teams_name(const char *const arr[], list_t *names,
    bool *is_ok)
{
    char *tmp = NULL;

    for (int i = 0; arr[i] != NULL && arr[i][0] != '-'; i++) {
        tmp = x_strdup(arr[i]);
        if (tmp == NULL) {
            *is_ok = false;
        }
        list_append(names, tmp, free, NULL);
    }
}

bool parse_arg_team_name(const char *const arr[], args_t *args)
{
    if (arr == NULL || arr[0] == NULL || x_strcmp(arr[0], "-n") != 0 ||
            args == NULL) {
        return false;
    }
    if (args->teams_name != NULL) {
        args->is_ok = false;
        return false;
    }
    args->teams_name = list_create();
    if (args->teams_name == NULL) {
        args->is_ok = false;
        return false;
    }
    add_teams_name(arr + 1, args->teams_name, &args->is_ok);
    if (args->teams_name->len == 0) {
        args->is_ok = false;
        return false;
    }
    return args->is_ok;
}
