/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** client_arg_test
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
    args_t args = {
        .clients_per_teams = 1,
        .teams_name = list_create(),
        .freq = 1,
        .height = 10,
        .width = 10,
        .is_ok = true,
        .port = port,
    };
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
        c->cl.ai.trantorien = trantorien_init("mdr", c->id, args.width, args.height);
        cr_assert_not_null(c->cl.ai.trantorien);
    }
}

Test(zappy, zappy_init)
{
    const char *av[] = {"bin_test", "-p", "4042", "-x", "15", "-y", "20", "-n", "abc", "def", "-c", "1", "-f", "1", NULL};
    args_t *args = args_init(14, av);
    zappy_t *zappy = zappy_init(args);

    cr_assert_not_null(args);
    cr_assert_not_null(zappy);
}

Test(zappy, zappy_init_fail)
{
    const char *av[] = {"bin_test", "-p", "4040", "-x", "15", "-y", "20", "-n", "abc", "def", "-c", "1", "-f", "-1", NULL};
    args_t *args = args_init(14, av);
    zappy_t *zappy = zappy_init(args);

    if (args != NULL) {
        cr_assert(args->is_ok == false);
    } else {
        cr_assert_fail();
    }
    cr_assert_null(zappy);
}

Test(loop_cmd_ai_move, move_north_border)
{
    zappy_t *zappy = NULL;

    set_up_tests(&zappy, 1, 9001);
    ntw_client_t *client = L_DATA(zappy->ntw->clients->start);
    cr_assert_not_null(client);
    client_t *c = L_DATA(client);
    cr_assert_not_null(c);
    c->cl.ai.trantorien->x = 0;
    c->cl.ai.trantorien->y = 0;
    cr_assert_eq(c->cl.ai.trantorien->x, 0);
    cr_assert_eq(c->cl.ai.trantorien->y, 0);
    c->cl.ai.trantorien->direction = NORTH;
    circular_buffer_write(client->read_from_outside, "Forward\n");
    while (circular_buffer_is_read_ready(client->write_to_outside) == false) {
        cr_assert_eq(loop(zappy, true), false);
    }
    cr_assert_str_eq(circular_buffer_read(client->write_to_outside), "ok\n");
    cr_assert_eq(c->cl.ai.trantorien->x, 0);
    cr_assert_eq(c->cl.ai.trantorien->y, zappy->map->height - 1);
}

Test(loop_cmd_ai_move, move_north)
{
    zappy_t *zappy = NULL;

    set_up_tests(&zappy, 1, 9002);
    ntw_client_t *client = L_DATA(zappy->ntw->clients->start);
    cr_assert_not_null(client);
    client_t *c = L_DATA(client);
    cr_assert_not_null(c);
    c->cl.ai.trantorien->x = 0;
    c->cl.ai.trantorien->y = 1;
    cr_assert_eq(c->cl.ai.trantorien->x, 0);
    cr_assert_eq(c->cl.ai.trantorien->y, 1);
    c->cl.ai.trantorien->direction = NORTH;
    circular_buffer_write(client->read_from_outside, "Forward\n");
    while (circular_buffer_is_read_ready(client->write_to_outside) == false) {
        cr_assert_eq(loop(zappy, true), false);
    }
    cr_assert_str_eq(circular_buffer_read(client->write_to_outside), "ok\n");
    cr_assert_eq(c->cl.ai.trantorien->x, 0);
    cr_assert_eq(c->cl.ai.trantorien->y, 0);
}

Test(loop_cmd_ai_move, move_north2)
{
    zappy_t *zappy = NULL;

    set_up_tests(&zappy, 1, 9003);
    ntw_client_t *client = L_DATA(zappy->ntw->clients->start);
    cr_assert_not_null(client);
    client_t *c = L_DATA(client);
    cr_assert_not_null(c);
    c->cl.ai.trantorien->x = 0;
    c->cl.ai.trantorien->y = 2;
    cr_assert_eq(c->cl.ai.trantorien->x, 0);
    cr_assert_eq(c->cl.ai.trantorien->y, 2);
    c->cl.ai.trantorien->direction = NORTH;
    circular_buffer_write(client->read_from_outside, "Forward\n");
    while (circular_buffer_is_read_ready(client->write_to_outside) == false) {
        cr_assert_eq(loop(zappy, true), false);
    }
    cr_assert_str_eq(circular_buffer_read(client->write_to_outside), "ok\n");
    cr_assert_eq(c->cl.ai.trantorien->x, 0);
    cr_assert_eq(c->cl.ai.trantorien->y, 1);
}

Test(loop_cmd_ai_move, move_south_border)
{
    zappy_t *zappy = NULL;

    set_up_tests(&zappy, 1, 9004);
    ntw_client_t *client = L_DATA(zappy->ntw->clients->start);
    cr_assert_not_null(client);
    client_t *c = L_DATA(client);
    cr_assert_not_null(c);
    c->cl.ai.trantorien->x = 0;
    c->cl.ai.trantorien->y = zappy->map->height - 1;
    cr_assert_eq(c->cl.ai.trantorien->x, 0);
    cr_assert_eq(c->cl.ai.trantorien->y, zappy->map->height - 1);
    c->cl.ai.trantorien->direction = SOUTH;
    circular_buffer_write(client->read_from_outside, "Forward\n");
    while (circular_buffer_is_read_ready(client->write_to_outside) == false) {
        cr_assert_eq(loop(zappy, true), false);
    }
    cr_assert_str_eq(circular_buffer_read(client->write_to_outside), "ok\n");
    cr_assert_eq(c->cl.ai.trantorien->x, 0);
    cr_assert_eq(c->cl.ai.trantorien->y, 0);
}

Test(loop_cmd_ai_move, move_south)
{
    zappy_t *zappy = NULL;

    set_up_tests(&zappy, 1, 9005);
    ntw_client_t *client = L_DATA(zappy->ntw->clients->start);
    cr_assert_not_null(client);
    client_t *c = L_DATA(client);
    cr_assert_not_null(c);
    c->cl.ai.trantorien->x = 0;
    c->cl.ai.trantorien->y = 0;
    cr_assert_eq(c->cl.ai.trantorien->x, 0);
    cr_assert_eq(c->cl.ai.trantorien->y, 0);
    c->cl.ai.trantorien->direction = SOUTH;
    circular_buffer_write(client->read_from_outside, "Forward\n");
    while (circular_buffer_is_read_ready(client->write_to_outside) == false) {
        cr_assert_eq(loop(zappy, true), false);
    }
    cr_assert_str_eq(circular_buffer_read(client->write_to_outside), "ok\n");
    cr_assert_eq(c->cl.ai.trantorien->x, 0);
    cr_assert_eq(c->cl.ai.trantorien->y, 1);
}

Test(loop_cmd_ai_move, move_south2)
{
    zappy_t *zappy = NULL;

    set_up_tests(&zappy, 1, 9006);
    ntw_client_t *client = L_DATA(zappy->ntw->clients->start);
    cr_assert_not_null(client);
    client_t *c = L_DATA(client);
    cr_assert_not_null(c);
    c->cl.ai.trantorien->x = 0;
    c->cl.ai.trantorien->y = zappy->map->height - 2;
    cr_assert_eq(c->cl.ai.trantorien->x, 0);
    cr_assert_eq(c->cl.ai.trantorien->y, zappy->map->height - 2);
    c->cl.ai.trantorien->direction = SOUTH;
    circular_buffer_write(client->read_from_outside, "Forward\n");
    while (circular_buffer_is_read_ready(client->write_to_outside) == false) {
        cr_assert_eq(loop(zappy, true), false);
    }
    cr_assert_str_eq(circular_buffer_read(client->write_to_outside), "ok\n");
    cr_assert_eq(c->cl.ai.trantorien->x, 0);
    cr_assert_eq(c->cl.ai.trantorien->y, zappy->map->height - 1);
}

Test(loop_cmd_ai_move, move_east_border)
{
    zappy_t *zappy = NULL;

    set_up_tests(&zappy, 1, 9007);
    ntw_client_t *client = L_DATA(zappy->ntw->clients->start);
    cr_assert_not_null(client);
    client_t *c = L_DATA(client);
    cr_assert_not_null(c);
    c->cl.ai.trantorien->x = zappy->map->width - 1;
    c->cl.ai.trantorien->y = 0;
    cr_assert_eq(c->cl.ai.trantorien->x, zappy->map->width - 1);
    cr_assert_eq(c->cl.ai.trantorien->y, 0);
    c->cl.ai.trantorien->direction = EAST;
    circular_buffer_write(client->read_from_outside, "Forward\n");
    while (circular_buffer_is_read_ready(client->write_to_outside) == false) {
        cr_assert_eq(loop(zappy, true), false);
    }
    cr_assert_str_eq(circular_buffer_read(client->write_to_outside), "ok\n");
    cr_assert_eq(c->cl.ai.trantorien->x, 0);
    cr_assert_eq(c->cl.ai.trantorien->y, 0);
}

Test(loop_cmd_ai_move, move_east)
{
    zappy_t *zappy = NULL;

    set_up_tests(&zappy, 1, 9008);
    ntw_client_t *client = L_DATA(zappy->ntw->clients->start);
    cr_assert_not_null(client);
    client_t *c = L_DATA(client);
    cr_assert_not_null(c);
    c->cl.ai.trantorien->x = 0;
    c->cl.ai.trantorien->y = 0;
    cr_assert_eq(c->cl.ai.trantorien->x, 0);
    cr_assert_eq(c->cl.ai.trantorien->y, 0);
    c->cl.ai.trantorien->direction = EAST;
    circular_buffer_write(client->read_from_outside, "Forward\n");
    while (circular_buffer_is_read_ready(client->write_to_outside) == false) {
        cr_assert_eq(loop(zappy, true), false);
    }
    cr_assert_str_eq(circular_buffer_read(client->write_to_outside), "ok\n");
    cr_assert_eq(c->cl.ai.trantorien->x, 1);
    cr_assert_eq(c->cl.ai.trantorien->y, 0);
}

Test(loop_cmd_ai_move, move_east2)
{
    zappy_t *zappy = NULL;

    set_up_tests(&zappy, 1, 9009);
    ntw_client_t *client = L_DATA(zappy->ntw->clients->start);
    cr_assert_not_null(client);
    client_t *c = L_DATA(client);
    cr_assert_not_null(c);
    c->cl.ai.trantorien->x = zappy->map->width - 2;
    c->cl.ai.trantorien->y = 0;
    cr_assert_eq(c->cl.ai.trantorien->x, zappy->map->width - 2);
    cr_assert_eq(c->cl.ai.trantorien->y, 0);
    c->cl.ai.trantorien->direction = EAST;
    circular_buffer_write(client->read_from_outside, "Forward\n");
    while (circular_buffer_is_read_ready(client->write_to_outside) == false) {
        cr_assert_eq(loop(zappy, true), false);
    }
    cr_assert_str_eq(circular_buffer_read(client->write_to_outside), "ok\n");
    cr_assert_eq(c->cl.ai.trantorien->x, zappy->map->width - 1);
    cr_assert_eq(c->cl.ai.trantorien->y, 0);
}

Test(loop_cmd_ai_move, move_west_border)
{
    zappy_t *zappy = NULL;

    set_up_tests(&zappy, 1, 9010);
    ntw_client_t *client = L_DATA(zappy->ntw->clients->start);
    cr_assert_not_null(client);
    client_t *c = L_DATA(client);
    cr_assert_not_null(c);
    c->cl.ai.trantorien->x = 0;
    c->cl.ai.trantorien->y = 0;
    cr_assert_eq(c->cl.ai.trantorien->x, 0);
    cr_assert_eq(c->cl.ai.trantorien->y, 0);
    c->cl.ai.trantorien->direction = WEST;
    circular_buffer_write(client->read_from_outside, "Forward\n");
    while (circular_buffer_is_read_ready(client->write_to_outside) == false) {
        cr_assert_eq(loop(zappy, true), false);
    }
    cr_assert_str_eq(circular_buffer_read(client->write_to_outside), "ok\n");
    cr_assert_eq(c->cl.ai.trantorien->x, zappy->map->width - 1);
    cr_assert_eq(c->cl.ai.trantorien->y, 0);
}

Test(loop_cmd_ai_move, move_west)
{
    zappy_t *zappy = NULL;

    set_up_tests(&zappy, 1, 9012);
    ntw_client_t *client = L_DATA(zappy->ntw->clients->start);
    cr_assert_not_null(client);
    client_t *c = L_DATA(client);
    cr_assert_not_null(c);
    c->cl.ai.trantorien->x = zappy->map->width - 1;
    c->cl.ai.trantorien->y = 0;
    cr_assert_eq(c->cl.ai.trantorien->x, zappy->map->width - 1);
    cr_assert_eq(c->cl.ai.trantorien->y, 0);
    c->cl.ai.trantorien->direction = WEST;
    circular_buffer_write(client->read_from_outside, "Forward\n");
    while (circular_buffer_is_read_ready(client->write_to_outside) == false) {
        cr_assert_eq(loop(zappy, true), false);
    }
    cr_assert_str_eq(circular_buffer_read(client->write_to_outside), "ok\n");
    cr_assert_eq(c->cl.ai.trantorien->x, zappy->map->width - 2);
    cr_assert_eq(c->cl.ai.trantorien->y, 0);
}

Test(loop_cmd_ai_move, move_west2)
{
    zappy_t *zappy = NULL;

    set_up_tests(&zappy, 1, 9013);
    ntw_client_t *client = L_DATA(zappy->ntw->clients->start);
    cr_assert_not_null(client);
    client_t *c = L_DATA(client);
    cr_assert_not_null(c);
    c->cl.ai.trantorien->x = 1;
    c->cl.ai.trantorien->y = 0;
    cr_assert_eq(c->cl.ai.trantorien->x, 1);
    cr_assert_eq(c->cl.ai.trantorien->y, 0);
    c->cl.ai.trantorien->direction = WEST;
    circular_buffer_write(client->read_from_outside, "Forward\n");
    while (circular_buffer_is_read_ready(client->write_to_outside) == false) {
        cr_assert_eq(loop(zappy, true), false);
    }
    cr_assert_str_eq(circular_buffer_read(client->write_to_outside), "ok\n");
    cr_assert_eq(c->cl.ai.trantorien->x, 0);
    cr_assert_eq(c->cl.ai.trantorien->y, 0);
}
