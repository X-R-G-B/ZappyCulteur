/*
** EPITECH PROJECT, 2023
** zappy server args parse
** File description:
** height
*/

#include <stdbool.h>
#include "tlcstdlibs.h"
#include "tlcstrings.h"
#include "args.h"
#include "internal.h"

bool parse_arg_height(const char *const arr[], args_t *args)
{
    if (arr == NULL || arr[0] == NULL || x_strcmp(arr[0], "-y") != 0 ||
            args == NULL) {
        return false;
    }
    if (args->height != 0) {
        args->is_ok = false;
        return false;
    }
    args->height = x_atoi(arr[1]);
    if (args->height <= 0) {
        args->is_ok = false;
        return false;
    }
    return true;
}
