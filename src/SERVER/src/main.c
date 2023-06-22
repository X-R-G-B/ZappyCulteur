/*
** EPITECH PROJECT, 2023
** zappy server
** File description:
** main
*/

#include <stdbool.h>
#include "args.h"
#include "zappy.h"

int main(int ac, const char *const av[])
{
    args_t *args = NULL;
    int status = 0;

    args = args_init(ac, av);
    if (args == NULL || args->is_ok == false) {
        args_destroy(args);
        return (84);
    }
    if (args->is_help != true) {
        args_debug(args);
        status = server_start(args);
    }
    args_destroy(args);
    return (status);
}
