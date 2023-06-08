/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** refuse_client_connection
*/

#include <stdio.h>
#include "circular_buffer.h"
#include "ntw.h"

void refuse_client_connection(ntw_t *ntw, ntw_client_t *cl)
{
    printf("ERROR: no trantorien available\n");
    if (ntw == NULL || cl == NULL) {
        return;
    }
    circular_buffer_write(cl->write_to_outside, "ko\n");
    list_append(ntw->clients_to_remove, cl, NULL, NULL);
}
