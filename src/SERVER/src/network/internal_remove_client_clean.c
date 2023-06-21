/*
** EPITECH PROJECT, 2023
** zappy server ntw
** File description:
** remove client clean
*/

#include <stdio.h>
#include "ntw.h"
#include "llog.h"
#include "ntw_internal.h"
#include "tlcllists.h"

static const char *format_err = "can't find client to disconnect";

void internal_remove_client_clean(ntw_t *ntw)
{
    ntw_client_t *cl = NULL;

    for (L_EACH(client, ntw->clients_to_remove)) {
        cl = L_DATA(client);
        if (list_remove_ptrdata(ntw->clients, cl) == 0) {
            llog_write_f(LOG_FILE_NETWORK, LLOG_WARNING, "%s", format_err);
        }
    }
    if (ntw->clients_to_remove != NULL && ntw->clients_to_remove->len != 0) {
        llog_write_f(LOG_FILE_NETWORK, LLOG_WARNING, "removing %d clients",
            ntw->clients_to_remove->len);
    }
    while (L_FIRST(ntw->clients_to_remove) != NULL) {
        list_remove_start(ntw->clients_to_remove);
    }
}
