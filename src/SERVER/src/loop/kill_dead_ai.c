/*
** EPITECH PROJECT, 2023
** zappy server loop
** File description:
** remove dead ai from the list of client
*/

#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include "circular_buffer.h"
#include "llog.h"
#include "ntw.h"
#include "client.h"
#include "tlcllists.h"
#include "trantorien.h"
#include "zappy.h"

static const char *format_egg = "%d dead eggs removed";

static const char *format_ai = "%d dead client AI removed";

static int kill_dead_egg(zappy_t *zappy)
{
    trantorien_t *trnt = NULL;
    list_t *lst = list_create();
    int nb_rm = 0;

    for (L_EACH(node, zappy->trantoriens_available)) {
        trnt = L_DATA(node);
        if (trnt == NULL || trnt->alive == true) {
            continue;
        }
        list_append(lst, node, NULL, NULL);
        nb_rm++;
    }
    for (L_EACH(node, lst)) {
        list_remove_ptrnode(zappy->trantoriens_available, L_DATA(node));
    }
    list_delete(lst);
    return nb_rm;
}

static int kill_dead_trnt(zappy_t *zappy)
{
    client_t *cl = NULL;
    ntw_client_t *ntw_cl = NULL;
    int nb_rm = 0;

    for (L_EACH(node, zappy->ntw->clients)) {
        ntw_cl = L_DATA(node);
        cl = L_DATA(ntw_cl);
        if (ntw_cl == NULL || cl == NULL || cl->type != AI ||
                cl->cl.ai.trantorien->alive == true ||
                circular_buffer_is_read_ready(ntw_cl->write_to_outside) ==
                false) {
            continue;
        }
        list_append(zappy->ntw->clients_to_remove, node->data, NULL, NULL);
        nb_rm++;
    }
    return nb_rm;
}

void kill_dead_ai(zappy_t *zappy)
{
    int nb_rm_egg = 0;
    int nb_rm_trnt = 0;

    if (zappy == NULL) {
        return;
    }
    nb_rm_egg = kill_dead_egg(zappy);
    nb_rm_trnt = kill_dead_trnt(zappy);
    if (nb_rm_egg != 0) {
        llog_write_fd(STDERR_FILENO, LLOG_INFO, format_egg, nb_rm_egg);
    }
    if (nb_rm_trnt != 0) {
        llog_write_fd(STDERR_FILENO, LLOG_INFO, format_ai, nb_rm_trnt);
    }
}
