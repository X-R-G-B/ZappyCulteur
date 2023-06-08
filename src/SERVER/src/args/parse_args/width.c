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
    if (arr == NULL || arr[0] == NULL || x_strcmp(arr[0], ARG_WIDTH) != 0 ||
            args == NULL || arr[1] == NULL) {
        return false;
    }
    if (args->width != 0 || x_strcontainc("123456789", arr[1][0]) != 1) {
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
