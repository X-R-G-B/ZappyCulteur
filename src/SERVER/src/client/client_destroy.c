/*
** EPITECH PROJECT, 2023
** zappy server client
** File description:
** destroy
*/

#include <stdio.h>
#include <stdlib.h>
#include "client.h"

// TODO: proper way to delete
void client_destroy(client_t *cl)
{
    if (cl == NULL) {
        return;
    }
    printf("%s%d\n", "INFO: client destroyed: ", cl->id);
}
