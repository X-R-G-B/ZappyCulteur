/*
** EPITECH PROJECT, 2023
** zappy server
** File description:
** main
*/

#include <stdbool.h>
#include "args.h"
#include "ntw.h"
#include "zappy.h"

static int server_start(args_t *args)
{
    bool is_end = false;
    zappy_t *zappy = NULL;

    zappy = zappy_init(args);
    if (zappy == NULL) {
        return (84);
    }
    while (is_end == false) {
        ntw_wait_till_events(zappy->ntw, 0, 0);
        ntw_loop(zappy->ntw);
        is_end = loop(zappy);
    }
    zappy_destroy(zappy);
    return 0;
}

int main(int ac, const char *const av[])
{
    args_t *args = NULL;
    int status = 0;

    args = args_init(ac, av);
    if (args == NULL || args->is_ok == false) {
        args_destroy(args);
        return (84);
    }
    args_debug(args);
    status = server_start(args);
    args_destroy(args);
    return (status);
}
