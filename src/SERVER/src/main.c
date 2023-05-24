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
    ntw_t *ntw = NULL;
    bool is_end = false;

    ntw = ntw_init(args->port, args->teams_name->len, on_new_conn);
    if (ntw == NULL) {
        return (84);
    }
    while (is_end == false) {
        ntw_wait_till_events(ntw, 0, 0);
        ntw_loop(ntw);
        is_end = loop(ntw, args);
    }
    ntw_destroy(ntw);
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
