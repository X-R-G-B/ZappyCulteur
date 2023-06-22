/*
** EPITECH PROJECT, 2023
** zappy server args parse
** File description:
** port
*/

#include <stdbool.h>
#include "tlcstdlibs.h"
#include "tlcstrings.h"
#include "args.h"
#include "internal.h"

bool parse_arg_port(const char *const arr[], args_t *args)
{
    if (arr == NULL || arr[0] == NULL || x_strcmp(arr[0], ARG_PORT) != 0 ||
            args == NULL || arr[1] == NULL) {
        return false;
    }
    if (args->port != -1 || x_strcontainc(OK_IINT, arr[1][0]) != 1) {
        args->is_ok = false;
        return false;
    }
    args->port = x_atoi(arr[1]);
    if (args->port < 0) {
        args->is_ok = false;
        return false;
    }
    return true;
}
