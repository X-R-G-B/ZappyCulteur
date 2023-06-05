/*
** EPITECH PROJECT, 2023
** zappy server args parse
** File description:
** width
*/

#include <stdbool.h>
#include "tlcstdlibs.h"
#include "args.h"
#include "tlcstrings.h"
#include "internal.h"

bool parse_arg_width(const char *const arr[], args_t *args)
{
    if (arr == NULL || arr[0] == NULL || x_strcmp(arr[0], "-x") != 0 ||
            args == NULL) {
        return false;
    }
    if (args->width != 0) {
        args->is_ok = false;
        return false;
    }
    args->width = x_atoi(arr[1]);
    if (args->width <= 0) {
        args->is_ok = false;
        return false;
    }
    return true;
}
