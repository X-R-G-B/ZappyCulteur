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

bool parse_arg_freq(const char *const arr[], args_t *args)
{
    if (arr == NULL || arr[0] == NULL || x_strcmp(arr[0], ARG_FREQ) != 0 ||
            args == NULL || arr[1] == NULL) {
        return false;
    }
    if (args->freq != 0 || x_strcontainc("123456789", arr[1][0]) != 1) {
        args->is_ok = false;
        return false;
    }
    args->freq = x_atoi(arr[1]);
    if (args->freq <= 0) {
        args->is_ok = false;
        return false;
    }
    return true;
}
