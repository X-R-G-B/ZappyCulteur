/*
** EPITECH PROJECT, 2023
** zappy server
** File description:
** main
*/

#include <stdbool.h>
#include <sys/select.h>
#include <time.h>
#include "args.h"
#include "ntw.h"
#include "zappy.h"

static int server_update(time_t *s_timeout, suseconds_t *m_timeout,
    zappy_t *zappy)
{
    int is_end = 0;
    bool new_freq = false;

    if (*s_timeout == 0 && *m_timeout == 0) {
        *s_timeout = zappy->args->freq;
        new_freq = true;
    }
    ntw_wait_till_events(zappy->ntw, s_timeout, m_timeout);
    ntw_loop(zappy->ntw);
    is_end = loop(zappy, new_freq);
    return is_end;
}

static int server_start(args_t *args)
{
    bool is_end = false;
    zappy_t *zappy = NULL;
    time_t s_timeout = 0;
    suseconds_t m_timeout = 0;

    zappy = zappy_init(args);
    if (zappy == NULL) {
        return (84);
    }
    while (is_end == false) {
        is_end = server_update(&s_timeout, &m_timeout, zappy);
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
