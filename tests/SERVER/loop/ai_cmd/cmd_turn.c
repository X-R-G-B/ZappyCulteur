/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** cmd_turn
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

Test(loop_cmd_ai_turn, turn_right_from_north)
{
    zappy_t *zappy = NULL;

    set_up_tests(&zappy, 1, 9014);
    ntw_client_t *client = L_DATA(zappy->ntw->clients->start);
    cr_assert_not_null(client);
    client_t *c = L_DATA(client);
    cr_assert_not_null(c);
    c->cl.ai.trantorien->x = 1;
    c->cl.ai.trantorien->y = 1;
    c->cl.ai.trantorien->direction = NORTH;
    circular_buffer_write(client->read_from_outside, "Right\n");
    while (circular_buffer_is_read_ready(client->write_to_outside) == false) {
        cr_assert_eq(loop(zappy, true), false);
    }
    cr_assert_eq(c->cl.ai.trantorien->direction, EAST);
}

Test(loop_cmd_ai_turn, turn_right_from_east)
{
    zappy_t *zappy = NULL;

    set_up_tests(&zappy, 1, 9015);
    ntw_client_t *client = L_DATA(zappy->ntw->clients->start);
    cr_assert_not_null(client);
    client_t *c = L_DATA(client);
    cr_assert_not_null(c);
    c->cl.ai.trantorien->x = 1;
    c->cl.ai.trantorien->y = 1;
    c->cl.ai.trantorien->direction = EAST;
    circular_buffer_write(client->read_from_outside, "Right\n");
    while (circular_buffer_is_read_ready(client->write_to_outside) == false) {
        cr_assert_eq(loop(zappy, true), false);
    }
    cr_assert_eq(c->cl.ai.trantorien->direction, SOUTH);
}

Test(loop_cmd_ai_turn, turn_right_from_south)
{
    zappy_t *zappy = NULL;

    set_up_tests(&zappy, 1, 9016);
    ntw_client_t *client = L_DATA(zappy->ntw->clients->start);
    cr_assert_not_null(client);
    client_t *c = L_DATA(client);
    cr_assert_not_null(c);
    c->cl.ai.trantorien->x = 1;
    c->cl.ai.trantorien->y = 1;
    c->cl.ai.trantorien->direction = SOUTH;
    circular_buffer_write(client->read_from_outside, "Right\n");
    while (circular_buffer_is_read_ready(client->write_to_outside) == false) {
        cr_assert_eq(loop(zappy, true), false);
    }
    cr_assert_eq(c->cl.ai.trantorien->direction, WEST);
}

Test(loop_cmd_ai_turn, turn_right_from_west)
{
    zappy_t *zappy = NULL;

    set_up_tests(&zappy, 1, 9017);
    ntw_client_t *client = L_DATA(zappy->ntw->clients->start);
    cr_assert_not_null(client);
    client_t *c = L_DATA(client);
    cr_assert_not_null(c);
    c->cl.ai.trantorien->x = 1;
    c->cl.ai.trantorien->y = 1;
    c->cl.ai.trantorien->direction = WEST;
    circular_buffer_write(client->read_from_outside, "Right\n");
    while (circular_buffer_is_read_ready(client->write_to_outside) == false) {
        cr_assert_eq(loop(zappy, true), false);
    }
    cr_assert_eq(c->cl.ai.trantorien->direction, NORTH);
}

Test(loop_cmd_ai_turn, turn_left_from_north)
{
    zappy_t *zappy = NULL;

    set_up_tests(&zappy, 1, 9018);
    ntw_client_t *client = L_DATA(zappy->ntw->clients->start);
    cr_assert_not_null(client);
    client_t *c = L_DATA(client);
    cr_assert_not_null(c);
    c->cl.ai.trantorien->x = 1;
    c->cl.ai.trantorien->y = 1;
    c->cl.ai.trantorien->direction = NORTH;
    circular_buffer_write(client->read_from_outside, "Left\n");
    while (circular_buffer_is_read_ready(client->write_to_outside) == false) {
        cr_assert_eq(loop(zappy, true), false);
    }
    cr_assert_eq(c->cl.ai.trantorien->direction, WEST);
}

Test(loop_cmd_ai_turn, turn_left_from_east)
{
    zappy_t *zappy = NULL;

    set_up_tests(&zappy, 1, 9019);
    ntw_client_t *client = L_DATA(zappy->ntw->clients->start);
    cr_assert_not_null(client);
    client_t *c = L_DATA(client);
    cr_assert_not_null(c);
    c->cl.ai.trantorien->x = 1;
    c->cl.ai.trantorien->y = 1;
    c->cl.ai.trantorien->direction = EAST;
    circular_buffer_write(client->read_from_outside, "Left\n");
    while (circular_buffer_is_read_ready(client->write_to_outside) == false) {
        cr_assert_eq(loop(zappy, true), false);
    }
    cr_assert_eq(c->cl.ai.trantorien->direction, NORTH);
}

Test(loop_cmd_ai_turn, turn_left_from_south)
{
    zappy_t *zappy = NULL;

    set_up_tests(&zappy, 1, 9020);
    ntw_client_t *client = L_DATA(zappy->ntw->clients->start);
    cr_assert_not_null(client);
    client_t *c = L_DATA(client);
    cr_assert_not_null(c);
    c->cl.ai.trantorien->x = 1;
    c->cl.ai.trantorien->y = 1;
    c->cl.ai.trantorien->direction = SOUTH;
    circular_buffer_write(client->read_from_outside, "Left\n");
    while (circular_buffer_is_read_ready(client->write_to_outside) == false) {
        cr_assert_eq(loop(zappy, true), false);
    }
    cr_assert_eq(c->cl.ai.trantorien->direction, EAST);
}

Test(loop_cmd_ai_turn, turn_left_from_west)
{
    zappy_t *zappy = NULL;

    set_up_tests(&zappy, 1, 9021);
    ntw_client_t *client = L_DATA(zappy->ntw->clients->start);
    cr_assert_not_null(client);
    client_t *c = L_DATA(client);
    cr_assert_not_null(c);
    c->cl.ai.trantorien->x = 1;
    c->cl.ai.trantorien->y = 1;
    c->cl.ai.trantorien->direction = WEST;
    circular_buffer_write(client->read_from_outside, "Left\n");
    while (circular_buffer_is_read_ready(client->write_to_outside) == false) {
        cr_assert_eq(loop(zappy, true), false);
    }
    cr_assert_eq(c->cl.ai.trantorien->direction, SOUTH);
}
