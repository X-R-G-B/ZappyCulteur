/*
** EPITECH PROJECT, 2023
** zappy server client
** File description:
** init
*/

#include <stdlib.h>
#include <string.h>
#include "client.h"

client_t *client_init(void)
{
    client_t *cl = NULL;

    cl = malloc(sizeof(client_t));
    if (cl == NULL) {
        return NULL;
    }
    memset(cl, 0, sizeof(client_t));
    cl->state = NOT_CONNECTED;
    return cl;
}
