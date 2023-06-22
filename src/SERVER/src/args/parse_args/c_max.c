/*
** EPITECH PROJECT, 2023
** zappy server args parse
** File description:
** client max
*/

#include <stdbool.h>
#include "tlcstrings.h"
#include "tlcstdlibs.h"
#include "internal.h"

bool parse_arg_c_max(const char *const arr[], args_t *args)
{
    if (arr == NULL || arr[0] == NULL || x_strcmp(arr[0], ARG_C_MAX) != 0 ||
            args == NULL || arr[1] == NULL) {
        return false;
    }
    if (args->client_max != DEFAULT_ARG_C_MAX ||
            x_strcontainc("123456789", arr[1][0]) != 1) {
        args->is_ok = false;
        return false;
    }
    args->client_max = x_atoi(arr[1]);
    if (args->client_max == 0 || args->client_max < -1) {
        args->is_ok = false;
        return false;
    }
    return true;
}
