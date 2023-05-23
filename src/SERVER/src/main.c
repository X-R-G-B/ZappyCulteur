/*
** EPITECH PROJECT, 2023
** zappy server
** File description:
** main
*/

#include <stdbool.h>
#include "args.h"
#include "ntw.h"

int main(int ac, const char *const av[])
{
    args_t *args = NULL;

    args = args_init(ac, av);
    if (args == NULL || args->is_ok == false) {
        args_destroy(args);
        return (84);
    }
    args_debug(args);
    args_destroy(args);
    return (0);
}
