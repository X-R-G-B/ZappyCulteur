/*
** EPITECH PROJECT, 2023
** zappy server args
** File description:
** debug
*/

#include <stdio.h>
#include "args.h"
#include "tlcllists.h"

void args_debug(args_t *args)
{
    char *tmp = NULL;

    if (args == NULL) {
        return;
    }
    printf("------ Args ------\n");
    printf("-c (clientsNb): %d\n", args->clients_per_teams);
    printf("-f (freq): %d\n", args->freq);
    printf("-p (port): %d\n", args->port);
    printf("-w (width): %d\n", args->width);
    printf("-h (height): %d\n", args->height);
    printf("-m (max client connected) (-1 = inf): %d\n", args->client_max);
    printf("-n (nameX):\n");
    for (L_EACH(tmpnode, args->teams_name)) {
        tmp = L_DATA(tmpnode);
        printf("\t%s\n", tmp);
    }
    printf("------------------\n");
}
