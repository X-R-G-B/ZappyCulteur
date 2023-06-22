#include <criterion/criterion.h>
#include <stdbool.h>
#include <stdio.h>

#include "args.h"
#include "circular_buffer.h"
#include "map.h"
#include "ntw.h"
#include "client.h"
#include "tlcllists.h"
#include "trantorien.h"
#include "zappy.h"
#include "../../../src/network/ntw_internal.h"
#include "command_reponses.h"

static void set_up_tests(zappy_t **zappy, int nb_client, int port,
    ntw_client_t **graphic)
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
        c->height = args.height;
        c->width = args.width;
        cr_assert_not_null(c->cl.ai.trantorien);
    }
    if (graphic != NULL) {
        *graphic = ntw_client_init(1);
        list_append((*zappy)->ntw->clients, *graphic, NULL, NULL);
        (*zappy)->ntw->on_new_conn(*graphic);
        client_t *c = L_DATA(*graphic);
        c->cl.graphic.tmp = 0;
        c->id = get_id();
        strcpy(c->name, "GRAPHIC");
        c->type = GRAPHIC;
        c->state = CONNECTED;
    }
}

/*
 * R: receiver (direction: NORTH(1))
 * E: emitter
  0   1   2   3   4   5   6   7   8   9
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 0
|---|---|---|---|---|---|---|---|---|---|
|   | 8 | 1 | 2 |   |   |   |   |   |   | 1
|---|---|---|---|---|---|---|---|---|---|
|   | 7 | R | 3 | E |   |   |   |   |   | 2
|---|---|---|---|---|---|---|---|---|---|
|   | 6 | 5 | 4 |   |   |   |   |   |   | 3
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 4
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 5
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 6
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 7
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 8
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 9
|---|---|---|---|---|---|---|---|---|---|
*/
Test(loop_cmd_ai_broadcast, basic)
{
    zappy_t *zappy = NULL;
    ntw_client_t *graph = NULL;

    set_up_tests(&zappy, 2, 8382, &graph);
    ntw_client_t *client_r = L_DATA(zappy->ntw->clients->start);
    ntw_client_t *client_e = L_DATA(zappy->ntw->clients->start->next);
    cr_assert_not_null(client_r);
    cr_assert_not_null(client_e);
    client_t *c_r = L_DATA(client_r);
    client_t *c_e = L_DATA(client_e);
    cr_assert_not_null(c_r);
    cr_assert_not_null(c_e);
    c_e->cl.ai.trantorien->x = 4;
    c_e->cl.ai.trantorien->y = 2;
    c_r->cl.ai.trantorien->x = 2;
    c_r->cl.ai.trantorien->y = 2;
    c_r->cl.ai.trantorien->direction = NORTH;
    circular_buffer_write(client_e->read_from_outside, "Broadcast ceci est un message\n");
    while (circular_buffer_is_read_ready(client_e->write_to_outside) == false) {
        cr_assert_eq(loop(zappy, true), false);
    }
    cr_assert_str_eq(circular_buffer_read(client_e->write_to_outside), OK_RESPONSE);
    cr_assert_eq(circular_buffer_read(client_e->write_to_outside), NULL);
    cr_assert_str_eq(circular_buffer_read(client_r->write_to_outside), "message 3, ceci est un message\n");
    cr_assert_eq(circular_buffer_read(client_r->write_to_outside), NULL);
}

/*
 * R: receiver (direction: EAST(2))
 * E: emitter
  0   1   2   3   4   5   6   7   8   9
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 0
|---|---|---|---|---|---|---|---|---|---|
|   | 6 | 7 | 8 |   |   |   |   |   |   | 1
|---|---|---|---|---|---|---|---|---|---|
|   | 5 | R | 1 | E |   |   |   |   |   | 2
|---|---|---|---|---|---|---|---|---|---|
|   | 4 | 3 | 2 |   |   |   |   |   |   | 3
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 4
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 5
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 6
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 7
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 8
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 9
|---|---|---|---|---|---|---|---|---|---|
*/
Test(loop_cmd_ai_broadcast, basic_1)
{
    zappy_t *zappy = NULL;
    ntw_client_t *graph = NULL;

    set_up_tests(&zappy, 2, 8383, &graph);
    ntw_client_t *client_r = L_DATA(zappy->ntw->clients->start);
    ntw_client_t *client_e = L_DATA(zappy->ntw->clients->start->next);
    cr_assert_not_null(client_r);
    cr_assert_not_null(client_e);
    client_t *c_r = L_DATA(client_r);
    client_t *c_e = L_DATA(client_e);
    cr_assert_not_null(c_r);
    cr_assert_not_null(c_e);
    c_e->cl.ai.trantorien->x = 4;
    c_e->cl.ai.trantorien->y = 2;
    c_r->cl.ai.trantorien->x = 2;
    c_r->cl.ai.trantorien->y = 2;
    c_r->cl.ai.trantorien->direction = EAST;
    circular_buffer_write(client_e->read_from_outside, "Broadcast ceci est un message\n");
    while (circular_buffer_is_read_ready(client_e->write_to_outside) == false) {
        cr_assert_eq(loop(zappy, true), false);
    }
    cr_assert_str_eq(circular_buffer_read(client_e->write_to_outside), OK_RESPONSE);
    cr_assert_eq(circular_buffer_read(client_e->write_to_outside), NULL);
    cr_assert_str_eq(circular_buffer_read(client_r->write_to_outside), "message 1, ceci est un message\n");
    cr_assert_eq(circular_buffer_read(client_r->write_to_outside), NULL);
}

/*
 * R: receiver (direction: SOUTH(3))
 * E: emitter
  0   1   2   3   4   5   6   7   8   9
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 0
|---|---|---|---|---|---|---|---|---|---|
|   | 4 | 5 | 6 |   |   |   |   |   |   | 1
|---|---|---|---|---|---|---|---|---|---|
|   | 3 | R | 7 | E |   |   |   |   |   | 2
|---|---|---|---|---|---|---|---|---|---|
|   | 2 | 1 | 8 |   |   |   |   |   |   | 3
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 4
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 5
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 6
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 7
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 8
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 9
|---|---|---|---|---|---|---|---|---|---|
*/
Test(loop_cmd_ai_broadcast, basic_2)
{
    zappy_t *zappy = NULL;
    ntw_client_t *graph = NULL;

    set_up_tests(&zappy, 2, 8384, &graph);
    ntw_client_t *client_r = L_DATA(zappy->ntw->clients->start);
    ntw_client_t *client_e = L_DATA(zappy->ntw->clients->start->next);
    cr_assert_not_null(client_r);
    cr_assert_not_null(client_e);
    client_t *c_r = L_DATA(client_r);
    client_t *c_e = L_DATA(client_e);
    cr_assert_not_null(c_r);
    cr_assert_not_null(c_e);
    c_e->cl.ai.trantorien->x = 4;
    c_e->cl.ai.trantorien->y = 2;
    c_r->cl.ai.trantorien->x = 2;
    c_r->cl.ai.trantorien->y = 2;
    c_r->cl.ai.trantorien->direction = SOUTH;
    circular_buffer_write(client_e->read_from_outside, "Broadcast ceci est un message\n");
    while (circular_buffer_is_read_ready(client_e->write_to_outside) == false) {
        cr_assert_eq(loop(zappy, true), false);
    }
    cr_assert_str_eq(circular_buffer_read(client_e->write_to_outside), OK_RESPONSE);
    cr_assert_eq(circular_buffer_read(client_e->write_to_outside), NULL);
    cr_assert_str_eq(circular_buffer_read(client_r->write_to_outside), "message 7, ceci est un message\n");
    cr_assert_eq(circular_buffer_read(client_r->write_to_outside), NULL);
}

/*
 * R: receiver (direction: WEST(4))
 * E: emitter
  0   1   2   3   4   5   6   7   8   9
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 0
|---|---|---|---|---|---|---|---|---|---|
|   | 2 | 3 | 4 |   |   |   |   |   |   | 1
|---|---|---|---|---|---|---|---|---|---|
|   | 1 | R | 5 | E |   |   |   |   |   | 2
|---|---|---|---|---|---|---|---|---|---|
|   | 8 | 7 | 6 |   |   |   |   |   |   | 3
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 4
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 5
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 6
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 7
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 8
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 9
|---|---|---|---|---|---|---|---|---|---|
*/
Test(loop_cmd_ai_broadcast, basic_3)
{
    zappy_t *zappy = NULL;
    ntw_client_t *graph = NULL;

    set_up_tests(&zappy, 2, 8385, &graph);
    ntw_client_t *client_r = L_DATA(zappy->ntw->clients->start);
    ntw_client_t *client_e = L_DATA(zappy->ntw->clients->start->next);
    cr_assert_not_null(client_r);
    cr_assert_not_null(client_e);
    client_t *c_r = L_DATA(client_r);
    client_t *c_e = L_DATA(client_e);
    cr_assert_not_null(c_r);
    cr_assert_not_null(c_e);
    c_e->cl.ai.trantorien->x = 4;
    c_e->cl.ai.trantorien->y = 2;
    c_r->cl.ai.trantorien->x = 2;
    c_r->cl.ai.trantorien->y = 2;
    c_r->cl.ai.trantorien->direction = WEST;
    circular_buffer_write(client_e->read_from_outside, "Broadcast ceci est un message\n");
    while (circular_buffer_is_read_ready(client_e->write_to_outside) == false) {
        cr_assert_eq(loop(zappy, true), false);
    }
    cr_assert_str_eq(circular_buffer_read(client_e->write_to_outside), OK_RESPONSE);
    cr_assert_eq(circular_buffer_read(client_e->write_to_outside), NULL);
    cr_assert_str_eq(circular_buffer_read(client_r->write_to_outside), "message 5, ceci est un message\n");
    cr_assert_eq(circular_buffer_read(client_r->write_to_outside), NULL);
}

/*
 * R: receiver (direction: WEST(4))
 * E: emitter
  0   1   2   3   4   5   6   7   8   9
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 0
|---|---|---|---|---|---|---|---|---|---|
|   | 2 | 3 | 4 |   |   |   |   |   |   | 1
|---|---|---|---|---|---|---|---|---|---|
|   | 1 | R | 5 |   |   |   |   |   |   | 2
|---|---|---|---|---|---|---|---|---|---|
|   | 8 | 7 | 6 |   |   |   |   |   |   | 3
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   | E |   |   |   |   |   | 4
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 5
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 6
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 7
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 8
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 9
|---|---|---|---|---|---|---|---|---|---|
*/
Test(loop_cmd_ai_broadcast, basic_4)
{
    zappy_t *zappy = NULL;
    ntw_client_t *graph = NULL;

    set_up_tests(&zappy, 2, 8386, &graph);
    ntw_client_t *client_r = L_DATA(zappy->ntw->clients->start);
    ntw_client_t *client_e = L_DATA(zappy->ntw->clients->start->next);
    cr_assert_not_null(client_r);
    cr_assert_not_null(client_e);
    client_t *c_r = L_DATA(client_r);
    client_t *c_e = L_DATA(client_e);
    cr_assert_not_null(c_r);
    cr_assert_not_null(c_e);
    c_e->cl.ai.trantorien->x = 4;
    c_e->cl.ai.trantorien->y = 4;
    c_r->cl.ai.trantorien->x = 2;
    c_r->cl.ai.trantorien->y = 2;
    c_r->cl.ai.trantorien->direction = WEST;
    circular_buffer_write(client_e->read_from_outside, "Broadcast ceci est un message\n");
    while (circular_buffer_is_read_ready(client_e->write_to_outside) == false) {
        cr_assert_eq(loop(zappy, true), false);
    }
    cr_assert_str_eq(circular_buffer_read(client_e->write_to_outside), OK_RESPONSE);
    cr_assert_eq(circular_buffer_read(client_e->write_to_outside), NULL);
    cr_assert_str_eq(circular_buffer_read(client_r->write_to_outside), "message 6, ceci est un message\n");
    cr_assert_eq(circular_buffer_read(client_r->write_to_outside), NULL);
}

/*
 * R: receiver (direction: WEST(4))
 * E: emitter
  0   1   2   3   4   5   6   7   8   9
|---|---|---|---|---|---|---|---|---|---|
| E |   |   |   |   |   |   |   |   |   | 0
|---|---|---|---|---|---|---|---|---|---|
|   | 2 | 3 | 4 |   |   |   |   |   |   | 1
|---|---|---|---|---|---|---|---|---|---|
|   | 1 | R | 5 |   |   |   |   |   |   | 2
|---|---|---|---|---|---|---|---|---|---|
|   | 8 | 7 | 6 |   |   |   |   |   |   | 3
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 4
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 5
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 6
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 7
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 8
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 9
|---|---|---|---|---|---|---|---|---|---|
*/
Test(loop_cmd_ai_broadcast, basic_5)
{
    zappy_t *zappy = NULL;
    ntw_client_t *graph = NULL;

    set_up_tests(&zappy, 2, 8387, &graph);
    ntw_client_t *client_r = L_DATA(zappy->ntw->clients->start);
    ntw_client_t *client_e = L_DATA(zappy->ntw->clients->start->next);
    cr_assert_not_null(client_r);
    cr_assert_not_null(client_e);
    client_t *c_r = L_DATA(client_r);
    client_t *c_e = L_DATA(client_e);
    cr_assert_not_null(c_r);
    cr_assert_not_null(c_e);
    c_e->cl.ai.trantorien->x = 0;
    c_e->cl.ai.trantorien->y = 0;
    c_r->cl.ai.trantorien->x = 2;
    c_r->cl.ai.trantorien->y = 2;
    c_r->cl.ai.trantorien->direction = WEST;
    circular_buffer_write(client_e->read_from_outside, "Broadcast ceci est un message\n");
    while (circular_buffer_is_read_ready(client_e->write_to_outside) == false) {
        cr_assert_eq(loop(zappy, true), false);
    }
    cr_assert_str_eq(circular_buffer_read(client_e->write_to_outside), OK_RESPONSE);
    cr_assert_eq(circular_buffer_read(client_e->write_to_outside), NULL);
    cr_assert_str_eq(circular_buffer_read(client_r->write_to_outside), "message 2, ceci est un message\n");
    cr_assert_eq(circular_buffer_read(client_r->write_to_outside), NULL);
}

/*
 * R: receiver (direction: WEST(4))
 * E: emitter
  0   1   2   3   4   5   6   7   8   9
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   | E |   |   |   |   |   | 0
|---|---|---|---|---|---|---|---|---|---|
|   | 2 | 3 | 4 |   |   |   |   |   |   | 1
|---|---|---|---|---|---|---|---|---|---|
|   | 1 | R | 5 |   |   |   |   |   |   | 2
|---|---|---|---|---|---|---|---|---|---|
|   | 8 | 7 | 6 |   |   |   |   |   |   | 3
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 4
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 5
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 6
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 7
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 8
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 9
|---|---|---|---|---|---|---|---|---|---|
*/
Test(loop_cmd_ai_broadcast, basic_6)
{
    zappy_t *zappy = NULL;
    ntw_client_t *graph = NULL;

    set_up_tests(&zappy, 2, 8388, &graph);
    ntw_client_t *client_r = L_DATA(zappy->ntw->clients->start);
    ntw_client_t *client_e = L_DATA(zappy->ntw->clients->start->next);
    cr_assert_not_null(client_r);
    cr_assert_not_null(client_e);
    client_t *c_r = L_DATA(client_r);
    client_t *c_e = L_DATA(client_e);
    cr_assert_not_null(c_r);
    cr_assert_not_null(c_e);
    c_e->cl.ai.trantorien->x = 4;
    c_e->cl.ai.trantorien->y = 0;
    c_r->cl.ai.trantorien->x = 2;
    c_r->cl.ai.trantorien->y = 2;
    c_r->cl.ai.trantorien->direction = WEST;
    circular_buffer_write(client_e->read_from_outside, "Broadcast ceci est un message\n");
    while (circular_buffer_is_read_ready(client_e->write_to_outside) == false) {
        cr_assert_eq(loop(zappy, true), false);
    }
    cr_assert_str_eq(circular_buffer_read(client_e->write_to_outside), OK_RESPONSE);
    cr_assert_eq(circular_buffer_read(client_e->write_to_outside), NULL);
    cr_assert_str_eq(circular_buffer_read(client_r->write_to_outside), "message 4, ceci est un message\n");
    cr_assert_eq(circular_buffer_read(client_r->write_to_outside), NULL);
}

/*
 * R: receiver (direction: WEST(4))
 * E: emitter
  0   1   2   3   4   5   6   7   8   9
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 0
|---|---|---|---|---|---|---|---|---|---|
|   | 2 | 3 | 4 |   |   |   |   |   |   | 1
|---|---|---|---|---|---|---|---|---|---|
|   | 1 | R | 5 |   |   |   |   |   |   | 2
|---|---|---|---|---|---|---|---|---|---|
|   | 8 | 7 | 6 |   |   |   |   |   |   | 3
|---|---|---|---|---|---|---|---|---|---|
| E |   |   |   |   |   |   |   |   |   | 4
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 5
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 6
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 7
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 8
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 9
|---|---|---|---|---|---|---|---|---|---|
*/
Test(loop_cmd_ai_broadcast, basic_7)
{
    zappy_t *zappy = NULL;
    ntw_client_t *graph = NULL;

    set_up_tests(&zappy, 2, 8389, &graph);
    ntw_client_t *client_r = L_DATA(zappy->ntw->clients->start);
    ntw_client_t *client_e = L_DATA(zappy->ntw->clients->start->next);
    cr_assert_not_null(client_r);
    cr_assert_not_null(client_e);
    client_t *c_r = L_DATA(client_r);
    client_t *c_e = L_DATA(client_e);
    cr_assert_not_null(c_r);
    cr_assert_not_null(c_e);
    c_e->cl.ai.trantorien->x = 0;
    c_e->cl.ai.trantorien->y = 4;
    c_r->cl.ai.trantorien->x = 2;
    c_r->cl.ai.trantorien->y = 2;
    c_r->cl.ai.trantorien->direction = WEST;
    circular_buffer_write(client_e->read_from_outside, "Broadcast ceci est un message\n");
    while (circular_buffer_is_read_ready(client_e->write_to_outside) == false) {
        cr_assert_eq(loop(zappy, true), false);
    }
    cr_assert_str_eq(circular_buffer_read(client_e->write_to_outside), OK_RESPONSE);
    cr_assert_eq(circular_buffer_read(client_e->write_to_outside), NULL);
    cr_assert_str_eq(circular_buffer_read(client_r->write_to_outside), "message 8, ceci est un message\n");
    cr_assert_eq(circular_buffer_read(client_r->write_to_outside), NULL);
}

/*
 * R: receiver (direction: WEST(4))
 * E: emitter
  0   1   2   3   4   5   6   7   8   9
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 0
|---|---|---|---|---|---|---|---|---|---|
|   | 2 | 3 | 4 |   |   |   |   |   |   | 1
|---|---|---|---|---|---|---|---|---|---|
|   | 1 | R | 5 |   |   |   |   | E |   | 2
|---|---|---|---|---|---|---|---|---|---|
|   | 8 | 7 | 6 |   |   |   |   |   |   | 3
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 4
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 5
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 6
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 7
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 8
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 9
|---|---|---|---|---|---|---|---|---|---|
*/
Test(loop_cmd_ai_broadcast, basic_8)
{
    zappy_t *zappy = NULL;
    ntw_client_t *graph = NULL;

    set_up_tests(&zappy, 2, 8390, &graph);
    ntw_client_t *client_r = L_DATA(zappy->ntw->clients->start);
    ntw_client_t *client_e = L_DATA(zappy->ntw->clients->start->next);
    cr_assert_not_null(client_r);
    cr_assert_not_null(client_e);
    client_t *c_r = L_DATA(client_r);
    client_t *c_e = L_DATA(client_e);
    cr_assert_not_null(c_r);
    cr_assert_not_null(c_e);
    c_e->cl.ai.trantorien->x = 8;
    c_e->cl.ai.trantorien->y = 2;
    c_r->cl.ai.trantorien->x = 2;
    c_r->cl.ai.trantorien->y = 2;
    c_r->cl.ai.trantorien->direction = WEST;
    circular_buffer_write(client_e->read_from_outside, "Broadcast ceci est un message\n");
    while (circular_buffer_is_read_ready(client_e->write_to_outside) == false) {
        cr_assert_eq(loop(zappy, true), false);
    }
    cr_assert_str_eq(circular_buffer_read(client_e->write_to_outside), OK_RESPONSE);
    cr_assert_eq(circular_buffer_read(client_e->write_to_outside), NULL);
    cr_assert_str_eq(circular_buffer_read(client_r->write_to_outside), "message 1, ceci est un message\n");
    cr_assert_eq(circular_buffer_read(client_r->write_to_outside), NULL);
}

/*
 * R: receiver (direction: WEST(4))
 * E: emitter
  0   1   2   3   4   5   6   7   8   9
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 0
|---|---|---|---|---|---|---|---|---|---|
|   | 2 | 3 | 4 |   |   |   |   |   |   | 1
|---|---|---|---|---|---|---|---|---|---|
|   | 1 | R | 5 |   |   |   |   |   |   | 2
|---|---|---|---|---|---|---|---|---|---|
|   | 8 | 7 | 6 |   |   |   |   |   |   | 3
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 4
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 5
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 6
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 7
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 8
|---|---|---|---|---|---|---|---|---|---|
|   |   | E |   |   |   |   |   |   |   | 9
|---|---|---|---|---|---|---|---|---|---|
*/
Test(loop_cmd_ai_broadcast, basic_9)
{
    zappy_t *zappy = NULL;
    ntw_client_t *graph = NULL;

    set_up_tests(&zappy, 2, 8391, &graph);
    ntw_client_t *client_r = L_DATA(zappy->ntw->clients->start);
    ntw_client_t *client_e = L_DATA(zappy->ntw->clients->start->next);
    cr_assert_not_null(client_r);
    cr_assert_not_null(client_e);
    client_t *c_r = L_DATA(client_r);
    client_t *c_e = L_DATA(client_e);
    cr_assert_not_null(c_r);
    cr_assert_not_null(c_e);
    c_e->cl.ai.trantorien->x = 2;
    c_e->cl.ai.trantorien->y = 9;
    c_r->cl.ai.trantorien->x = 2;
    c_r->cl.ai.trantorien->y = 2;
    c_r->cl.ai.trantorien->direction = WEST;
    circular_buffer_write(client_e->read_from_outside, "Broadcast ceci est un message\n");
    while (circular_buffer_is_read_ready(client_e->write_to_outside) == false) {
        cr_assert_eq(loop(zappy, true), false);
    }
    cr_assert_str_eq(circular_buffer_read(client_e->write_to_outside), OK_RESPONSE);
    cr_assert_eq(circular_buffer_read(client_e->write_to_outside), NULL);
    cr_assert_str_eq(circular_buffer_read(client_r->write_to_outside), "message 3, ceci est un message\n");
    cr_assert_eq(circular_buffer_read(client_r->write_to_outside), NULL);
}

/*
 * R: receiver (direction: WEST(4))
 * E: emitter
  0   1   2   3   4   5   6   7   8   9
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 0
|---|---|---|---|---|---|---|---|---|---|
|   | 2 | 3 | 4 |   |   |   |   |   |   | 1
|---|---|---|---|---|---|---|---|---|---|
|   | 1 | R | 5 |   |   |   |   |   |   | 2
|---|---|---|---|---|---|---|---|---|---|
|   | 8 | 7 | 6 |   |   |   |   |   |   | 3
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 4
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 5
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 6
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 7
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 8
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   | E | 9
|---|---|---|---|---|---|---|---|---|---|
*/
Test(loop_cmd_ai_broadcast, basic_10)
{
    zappy_t *zappy = NULL;
    ntw_client_t *graph = NULL;

    set_up_tests(&zappy, 2, 8392, &graph);
    ntw_client_t *client_r = L_DATA(zappy->ntw->clients->start);
    ntw_client_t *client_e = L_DATA(zappy->ntw->clients->start->next);
    cr_assert_not_null(client_r);
    cr_assert_not_null(client_e);
    client_t *c_r = L_DATA(client_r);
    client_t *c_e = L_DATA(client_e);
    cr_assert_not_null(c_r);
    cr_assert_not_null(c_e);
    c_e->cl.ai.trantorien->x = 9;
    c_e->cl.ai.trantorien->y = 9;
    c_r->cl.ai.trantorien->x = 2;
    c_r->cl.ai.trantorien->y = 2;
    c_r->cl.ai.trantorien->direction = WEST;
    circular_buffer_write(client_e->read_from_outside, "Broadcast ceci est un message\n");
    while (circular_buffer_is_read_ready(client_e->write_to_outside) == false) {
        cr_assert_eq(loop(zappy, true), false);
    }
    cr_assert_str_eq(circular_buffer_read(client_e->write_to_outside), OK_RESPONSE);
    cr_assert_eq(circular_buffer_read(client_e->write_to_outside), NULL);
    cr_assert_str_eq(circular_buffer_read(client_r->write_to_outside), "message 2, ceci est un message\n");
    cr_assert_eq(circular_buffer_read(client_r->write_to_outside), NULL);
}

/*
 * R: receiver (direction: WEST(4))
 * E: emitter
  0   1   2   3   4   5   6   7   8   9
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 0
|---|---|---|---|---|---|---|---|---|---|
|   | 2 | 3 | 4 |   |   |   |   |   |   | 1
|---|---|---|---|---|---|---|---|---|---|
|   | 1 | R | 5E|   |   |   |   |   |   | 2
|---|---|---|---|---|---|---|---|---|---|
|   | 8 | 7 | 6 |   |   |   |   |   |   | 3
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 4
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 5
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 6
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 7
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 8
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 9
|---|---|---|---|---|---|---|---|---|---|
*/
Test(loop_cmd_ai_broadcast, basic_11)
{
    zappy_t *zappy = NULL;
    ntw_client_t *graph = NULL;

    set_up_tests(&zappy, 2, 8393, &graph);
    ntw_client_t *client_r = L_DATA(zappy->ntw->clients->start);
    ntw_client_t *client_e = L_DATA(zappy->ntw->clients->start->next);
    cr_assert_not_null(client_r);
    cr_assert_not_null(client_e);
    client_t *c_r = L_DATA(client_r);
    client_t *c_e = L_DATA(client_e);
    cr_assert_not_null(c_r);
    cr_assert_not_null(c_e);
    c_e->cl.ai.trantorien->x = 3;
    c_e->cl.ai.trantorien->y = 2;
    c_r->cl.ai.trantorien->x = 2;
    c_r->cl.ai.trantorien->y = 2;
    c_r->cl.ai.trantorien->direction = WEST;
    circular_buffer_write(client_e->read_from_outside, "Broadcast ceci est un message\n");
    while (circular_buffer_is_read_ready(client_e->write_to_outside) == false) {
        cr_assert_eq(loop(zappy, true), false);
    }
    cr_assert_str_eq(circular_buffer_read(client_e->write_to_outside), OK_RESPONSE);
    cr_assert_eq(circular_buffer_read(client_e->write_to_outside), NULL);
    cr_assert_str_eq(circular_buffer_read(client_r->write_to_outside), "message 5, ceci est un message\n");
    cr_assert_eq(circular_buffer_read(client_r->write_to_outside), NULL);
}

/*
 * R: receiver (direction: WEST(4))
 * E: emitter
  0   1   2   3   4   5   6   7   8   9
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 0
|---|---|---|---|---|---|---|---|---|---|
|   | 2 | 3 | 4 |   |   |   |   |   |   | 1
|---|---|---|---|---|---|---|---|---|---|
|   | 1 | R | 5 |   |   |   |   |   |   | 2
|---|---|---|---|---|---|---|---|---|---|
|   | 8 | 7E| 6 |   |   |   |   |   |   | 3
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 4
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 5
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 6
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 7
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 8
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 9
|---|---|---|---|---|---|---|---|---|---|
*/
Test(loop_cmd_ai_broadcast, basic_12)
{
    zappy_t *zappy = NULL;
    ntw_client_t *graph = NULL;

    set_up_tests(&zappy, 2, 8394, &graph);
    ntw_client_t *client_r = L_DATA(zappy->ntw->clients->start);
    ntw_client_t *client_e = L_DATA(zappy->ntw->clients->start->next);
    cr_assert_not_null(client_r);
    cr_assert_not_null(client_e);
    client_t *c_r = L_DATA(client_r);
    client_t *c_e = L_DATA(client_e);
    cr_assert_not_null(c_r);
    cr_assert_not_null(c_e);
    c_e->cl.ai.trantorien->x = 2;
    c_e->cl.ai.trantorien->y = 3;
    c_r->cl.ai.trantorien->x = 2;
    c_r->cl.ai.trantorien->y = 2;
    c_r->cl.ai.trantorien->direction = WEST;
    circular_buffer_write(client_e->read_from_outside, "Broadcast ceci est un message\n");
    while (circular_buffer_is_read_ready(client_e->write_to_outside) == false) {
        cr_assert_eq(loop(zappy, true), false);
    }
    cr_assert_str_eq(circular_buffer_read(client_e->write_to_outside), OK_RESPONSE);
    cr_assert_eq(circular_buffer_read(client_e->write_to_outside), NULL);
    cr_assert_str_eq(circular_buffer_read(client_r->write_to_outside), "message 7, ceci est un message\n");
    cr_assert_eq(circular_buffer_read(client_r->write_to_outside), NULL);
}

/*
 * R: receiver (direction: NORTH(1))
 * E: emitter
  0   1   2   3   4   5   6   7   8   9
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 0
|---|---|---|---|---|---|---|---|---|---|
|   | 8 | 1 | 2 |   |   |   |   |   |   | 1
|---|---|---|---|---|---|---|---|---|---|
|   | 7 | R | 3 |   |   |   |   |   |   | 2
|---|---|---|---|---|---|---|---|---|---|
|   | 6 | 5E| 4 |   |   |   |   |   |   | 3
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 4
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 5
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 6
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 7
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 8
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 9
|---|---|---|---|---|---|---|---|---|---|
*/
Test(loop_cmd_ai_broadcast, basic_13)
{
    zappy_t *zappy = NULL;
    ntw_client_t *graph = NULL;

    set_up_tests(&zappy, 2, 8395, &graph);
    ntw_client_t *client_r = L_DATA(zappy->ntw->clients->start);
    ntw_client_t *client_e = L_DATA(zappy->ntw->clients->start->next);
    cr_assert_not_null(client_r);
    cr_assert_not_null(client_e);
    client_t *c_r = L_DATA(client_r);
    client_t *c_e = L_DATA(client_e);
    cr_assert_not_null(c_r);
    cr_assert_not_null(c_e);
    c_e->cl.ai.trantorien->x = 2;
    c_e->cl.ai.trantorien->y = 3;
    c_r->cl.ai.trantorien->x = 2;
    c_r->cl.ai.trantorien->y = 2;
    c_r->cl.ai.trantorien->direction = NORTH;
    circular_buffer_write(client_e->read_from_outside, "Broadcast ceci est un message\n");
    while (circular_buffer_is_read_ready(client_e->write_to_outside) == false) {
        cr_assert_eq(loop(zappy, true), false);
    }
    cr_assert_str_eq(circular_buffer_read(client_e->write_to_outside), OK_RESPONSE);
    cr_assert_eq(circular_buffer_read(client_e->write_to_outside), NULL);
    cr_assert_str_eq(circular_buffer_read(client_r->write_to_outside), "message 5, ceci est un message\n");
    cr_assert_eq(circular_buffer_read(client_r->write_to_outside), NULL);
}

/*
 * R: receiver (direction: NORTH(1))
 * E: emitter
  0   1   2   3   4   5   6   7   8   9
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 0
|---|---|---|---|---|---|---|---|---|---|
|   | 8 | 1E| 2 |   |   |   |   |   |   | 1
|---|---|---|---|---|---|---|---|---|---|
|   | 7 | R | 3 |   |   |   |   |   |   | 2
|---|---|---|---|---|---|---|---|---|---|
|   | 6 | 5 | 4 |   |   |   |   |   |   | 3
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 4
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 5
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 6
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 7
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 8
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 9
|---|---|---|---|---|---|---|---|---|---|
*/
Test(loop_cmd_ai_broadcast, basic_14)
{
    zappy_t *zappy = NULL;
    ntw_client_t *graph = NULL;

    set_up_tests(&zappy, 2, 8396, &graph);
    ntw_client_t *client_r = L_DATA(zappy->ntw->clients->start);
    ntw_client_t *client_e = L_DATA(zappy->ntw->clients->start->next);
    cr_assert_not_null(client_r);
    cr_assert_not_null(client_e);
    client_t *c_r = L_DATA(client_r);
    client_t *c_e = L_DATA(client_e);
    cr_assert_not_null(c_r);
    cr_assert_not_null(c_e);
    c_e->cl.ai.trantorien->x = 2;
    c_e->cl.ai.trantorien->y = 1;
    c_r->cl.ai.trantorien->x = 2;
    c_r->cl.ai.trantorien->y = 2;
    c_r->cl.ai.trantorien->direction = NORTH;
    circular_buffer_write(client_e->read_from_outside, "Broadcast ceci est un message\n");
    while (circular_buffer_is_read_ready(client_e->write_to_outside) == false) {
        cr_assert_eq(loop(zappy, true), false);
    }
    cr_assert_str_eq(circular_buffer_read(client_e->write_to_outside), OK_RESPONSE);
    cr_assert_eq(circular_buffer_read(client_e->write_to_outside), NULL);
    cr_assert_str_eq(circular_buffer_read(client_r->write_to_outside), "message 1, ceci est un message\n");
    cr_assert_eq(circular_buffer_read(client_r->write_to_outside), NULL);
}

/*
 * R: receiver (direction: NORTH(1))
 * E: emitter
  0   1   2   3   4   5   6   7   8   9
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 0
|---|---|---|---|---|---|---|---|---|---|
|   | 8 | 1 | 2 |   |   |   |   |   |   | 1
|---|---|---|---|---|---|---|---|---|---|
|   | 7 | RE| 3 |   |   |   |   |   |   | 2
|---|---|---|---|---|---|---|---|---|---|
|   | 6 | 5 | 4 |   |   |   |   |   |   | 3
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 4
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 5
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 6
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 7
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 8
|---|---|---|---|---|---|---|---|---|---|
|   |   |   |   |   |   |   |   |   |   | 9
|---|---|---|---|---|---|---|---|---|---|
*/
Test(loop_cmd_ai_broadcast, basic_15)
{
    zappy_t *zappy = NULL;
    ntw_client_t *graph = NULL;

    set_up_tests(&zappy, 2, 8397, &graph);
    ntw_client_t *client_r = L_DATA(zappy->ntw->clients->start);
    ntw_client_t *client_e = L_DATA(zappy->ntw->clients->start->next);
    cr_assert_not_null(client_r);
    cr_assert_not_null(client_e);
    client_t *c_r = L_DATA(client_r);
    client_t *c_e = L_DATA(client_e);
    cr_assert_not_null(c_r);
    cr_assert_not_null(c_e);
    c_e->cl.ai.trantorien->x = 2;
    c_e->cl.ai.trantorien->y = 2;
    c_r->cl.ai.trantorien->x = 2;
    c_r->cl.ai.trantorien->y = 2;
    c_r->cl.ai.trantorien->direction = NORTH;
    circular_buffer_write(client_e->read_from_outside, "Broadcast ceci est un message\n");
    while (circular_buffer_is_read_ready(client_e->write_to_outside) == false) {
        cr_assert_eq(loop(zappy, true), false);
    }
    cr_assert_str_eq(circular_buffer_read(client_e->write_to_outside), OK_RESPONSE);
    cr_assert_eq(circular_buffer_read(client_e->write_to_outside), NULL);
    cr_assert_str_eq(circular_buffer_read(client_r->write_to_outside), "message 0, ceci est un message\n");
    cr_assert_eq(circular_buffer_read(client_r->write_to_outside), NULL);
}
