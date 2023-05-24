/*
** EPITECH PROJECT, 2023
** zappy server ntw
** File description:
** remove client clean
*/

#include <stdio.h>
#include "ntw.h"
#include "ntw_internal.h"
#include "tlcllists.h"

void internal_remove_client_clean(ntw_t *ntw)
{
    ntw_client_t *cl = NULL;

    for (L_EACH(client, ntw->clients_to_remove)) {
        cl = L_DATA(client);
        if (list_remove_ptrdata(ntw->clients, cl) == 0) {
            fprintf(stderr, "ERROR: can't find client to disconnect\n");
        }
    }
    while (L_FIRST(ntw->clients_to_remove) != NULL) {
        list_remove_start(ntw->clients_to_remove);
    }
}
