/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** cmd_eject
*/

#include <criterion/criterion.h>
#include "args.h"
#include "circular_buffer.h"
#include "map.h"
#include "ntw.h"
#include "client.h"
#include "tlcllists.h"
#include "trantorien.h"
#include "zappy.h"
#include "../../../src/network/ntw_internal.h"

static void set_up_tests(zappy_t **zappy, int nb_client, int port)
{
    static args_t args = {
        .clients_per_teams = 1,
        .teams_name = NULL,
        .freq = 1000,
        .height = 10,
        .width = 10,
        .is_ok = true,
        .port = 0,
        .client_max = 10,
    };
    args.port = port;
    args.teams_name = list_create();
    *zappy = zappy_init(&args);
    ntw_client_t *client;

    cr_assert_not_null(*zappy);
    cr_assert_not_null((*zappy)->map);
    cr_assert_not_null((*zappy)->map->tiles);
    for (int i = 0; i < nb_client; i++) {
        client = ntw_client_init(1);
        list_append((*zappy)->ntw->clients, client, NULL, NULL);
        (*zappy)->ntw->on_new_conn(client);
    }
    for (L_EACH(x, (*zappy)->ntw->clients)) {
        ntw_client_t *client = L_DATA(x);
        client_t *c = L_DATA(client);

        cr_assert_not_null(c);
        c->id = get_id();
        strcpy(c->name, "test");
        c->state = CONNECTED;
        c->type = AI;
        c->cl.ai.trantorien = trantorien_init("mdr", args.width, args.height);
        c->cl.ai.trantorien->id = c->id;
        cr_assert_not_null(c->cl.ai.trantorien);
    }
}

Test(loop_cmd_eject, cmd_eject_test1)
{
    zappy_t *zappy = NULL;

    set_up_tests(&zappy, 2, 9201);
    for (L_EACH(x, zappy->ntw->clients)) {
        ntw_client_t *client = L_DATA(x);
        client_t *c = L_DATA(client);

        cr_assert_not_null(c);
        c->cl.ai.trantorien->x = 0;
        c->cl.ai.trantorien->y = 0;
        c->cl.ai.trantorien->direction = EAST;
    }
    ntw_client_t *client = L_DATA(list_index(zappy->ntw->clients, 0));
    cr_assert_not_null(client);
    client_t *c = L_DATA(client);
    cr_assert_not_null(c);
    circular_buffer_write(client->read_from_outside, "Eject\n");
    while (circular_buffer_is_read_ready(client->write_to_outside) == false) {
        cr_assert_eq(loop(zappy, true), false);
    }
    client = L_DATA(list_index(zappy->ntw->clients, 1));
    cr_assert_not_null(client);
    c = L_DATA(client);
    cr_assert_not_null(c);
    cr_assert_str_eq(circular_buffer_read(client->write_to_outside), "eject\n");
    cr_assert_eq(c->cl.ai.trantorien->x, 1);
    cr_assert_eq(c->cl.ai.trantorien->y, 0);
}

Test(loop_cmd_eject, cmd_eject_test2)
{
    zappy_t *zappy = NULL;
    trantorien_t *tr_src = NULL;

    set_up_tests(&zappy, 2, 9202);
    for (L_EACH(x, zappy->ntw->clients)) {
        ntw_client_t *client = L_DATA(x);
        client_t *c = L_DATA(client);

        cr_assert_not_null(c);
        c->cl.ai.trantorien->x = 0;
        c->cl.ai.trantorien->y = 0;
        c->cl.ai.trantorien->direction = EAST;
    }
    ntw_client_t *client = L_DATA(list_index(zappy->ntw->clients, 0));
    cr_assert_not_null(client);
    client_t *c = L_DATA(client);
    cr_assert_not_null(c);
    tr_src = trantorien_init(c->cl.ai.trantorien->team_name, 10, 10);
    cr_assert_not_null(tr_src);
    tr_src->x = 0;
    tr_src->y = 0;
    list_append(zappy->trantoriens_available, tr_src, (void (*) (void *)) trantorien_destroy, NULL);
    cr_assert_eq(zappy->trantoriens_available->len, 1);
    circular_buffer_write(client->read_from_outside, "Eject\n");
    while (circular_buffer_is_read_ready(client->write_to_outside) == false) {
        cr_assert_eq(loop(zappy, true), false);
    }
    client = L_DATA(list_index(zappy->ntw->clients, 1));
    cr_assert_not_null(client);
    c = L_DATA(client);
    cr_assert_not_null(c);
    cr_assert_str_eq(circular_buffer_read(client->write_to_outside), "eject\n");
    cr_assert_eq(c->cl.ai.trantorien->x, 1);
    cr_assert_eq(c->cl.ai.trantorien->y, 0);
    cr_assert_eq(zappy->trantoriens_available->len, 0);
    client = L_DATA(list_index(zappy->ntw->clients, 0));
    cr_assert_not_null(client);
    c = L_DATA(client);
    cr_assert_not_null(c);
    cr_assert_eq(c->cl.ai.trantorien->x, 0);
    cr_assert_eq(c->cl.ai.trantorien->y, 0);
}
