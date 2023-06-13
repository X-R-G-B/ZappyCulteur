/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** cmd_look_around
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
        c->cl.ai.trantorien = trantorien_init("mdr", args.width, args.height);
        c->cl.ai.trantorien->id = c->id;
        cr_assert_not_null(c->cl.ai.trantorien);
    }
}

/*
  0   1   2   3   4   5   6   7   8   9
|---|---|---|---|---|---|---|---|---|---|
| x |   | x |   | x |   | x |   | x |   | 0
|---|---|---|---|---|---|---|---|---|---|
| x |   | x |   | x |   | x |   | x |   | 1
|---|---|---|---|---|---|---|---|---|---|
| x |   | x |   | x |   | x |   | x |   | 2
|---|---|---|---|---|---|---|---|---|---|
| x |   | x |   | x |   | x |   | x |   | 3
|---|---|---|---|---|---|---|---|---|---|
| x |   | x |   | x |   | x |   | x |   | 4
|---|---|---|---|---|---|---|---|---|---|
| x |   | x |   | x |   | x |   | x |   | 5
|---|---|---|---|---|---|---|---|---|---|
| x |   | x |   | x |   | x |   | x |   | 6
|---|---|---|---|---|---|---|---|---|---|
| x |   | x |   | x |   | x |   | x |   | 7
|---|---|---|---|---|---|---|---|---|---|
| x |   | x |  1| x2|  3| x |   | x |   | 8
|---|---|---|---|---|---|---|---|---|---|
| x |   | x |   | T0|   | x |   | x |   | 9
|---|---|---|---|---|---|---|---|---|---|
*/
Test(loop_cmd_ai_look_around, look_from_north_level_1)
{
    zappy_t *zappy = NULL;

    set_up_tests(&zappy, 1, 9022);
    ntw_client_t *client = L_DATA(zappy->ntw->clients->start);
    cr_assert_not_null(client);
    client_t *c = L_DATA(client);
    cr_assert_not_null(c);
    c->cl.ai.trantorien->x = 4;
    c->cl.ai.trantorien->y = 9;
    c->cl.ai.trantorien->level = 1;
    c->cl.ai.trantorien->direction = NORTH;
    for (int i = 0; i < zappy->map->width * zappy->map->height; i++) {
        for (int j = 0; j < MAX_NB_RESOURCES; j++) {
            zappy->map->tiles[i].ressources[j] = (i % 2 == 0) ? 1 : 0;
        }
    }
    circular_buffer_write(client->read_from_outside, "Look\n");
    while (circular_buffer_is_read_ready(client->write_to_outside) == false) {
        cr_assert_eq(loop(zappy, true), false);
    }
    cr_assert_str_eq(circular_buffer_read(client->write_to_outside), "[food linemate deraumere sibur mendiane phiras thystame player,,food linemate deraumere sibur mendiane phiras thystame,]\n");
}

Test(loop_cmd_ai_look_around, look_from_east_level_1) {
    zappy_t *zappy = NULL;

    set_up_tests(&zappy, 1, 9023);
    ntw_client_t *client = L_DATA(zappy->ntw->clients->start);
    cr_assert_not_null(client);
    client_t *c = L_DATA(client);
    cr_assert_not_null(c);
    c->cl.ai.trantorien->x = 4;
    c->cl.ai.trantorien->y = 9;
    c->cl.ai.trantorien->level = 1;
    c->cl.ai.trantorien->direction = EAST;
    for (int i = 0; i < zappy->map->width * zappy->map->height; i++) {
        for (int j = 0; j < MAX_NB_RESOURCES; j++) {
            zappy->map->tiles[i].ressources[j] = (i % 2 == 0) ? 1 : 0;
        }
    }
    circular_buffer_write(client->read_from_outside, "Look\n");
    while (circular_buffer_is_read_ready(client->write_to_outside) == false) {
        cr_assert_eq(loop(zappy, true), false);
    }
    cr_assert_str_eq(circular_buffer_read(client->write_to_outside), "[food linemate deraumere sibur mendiane phiras thystame player,,,]\n");
}

Test(loop_cmd_ai_look_around, look_from_south_level_1)
{
    zappy_t *zappy = NULL;

    set_up_tests(&zappy, 1, 9024);
    ntw_client_t *client = L_DATA(zappy->ntw->clients->start);
    cr_assert_not_null(client);
    client_t *c = L_DATA(client);
    cr_assert_not_null(c);
    c->cl.ai.trantorien->x = 4;
    c->cl.ai.trantorien->y = 9;
    c->cl.ai.trantorien->level = 1;
    c->cl.ai.trantorien->direction = SOUTH;
    for (int i = 0; i < zappy->map->width * zappy->map->height; i++) {
        for (int j = 0; j < MAX_NB_RESOURCES; j++) {
            zappy->map->tiles[i].ressources[j] = (i % 2 == 0) ? 1 : 0;
        }
    }
    circular_buffer_write(client->read_from_outside, "Look\n");
    while (circular_buffer_is_read_ready(client->write_to_outside) == false) {
        cr_assert_eq(loop(zappy, true), false);
    }
    cr_assert_str_eq(circular_buffer_read(client->write_to_outside), "[food linemate deraumere sibur mendiane phiras thystame player,,food linemate deraumere sibur mendiane phiras thystame,]\n");
}

Test(loop_cmd_ai_look_around, look_from_south_level_1_test2)
{
    zappy_t *zappy = NULL;

    set_up_tests(&zappy, 1, 9124);
    ntw_client_t *client = L_DATA(zappy->ntw->clients->start);
    cr_assert_not_null(client);
    client_t *c = L_DATA(client);
    cr_assert_not_null(c);
    c->cl.ai.trantorien->x = 5;
    c->cl.ai.trantorien->y = 9;
    c->cl.ai.trantorien->level = 1;
    c->cl.ai.trantorien->direction = SOUTH;
    for (int i = 0; i < zappy->map->width * zappy->map->height; i++) {
        for (int j = 0; j < MAX_NB_RESOURCES; j++) {
            zappy->map->tiles[i].ressources[j] = (i % 2 == 0) ? 1 : 0;
        }
    }
    circular_buffer_write(client->read_from_outside, "Look\n");
    while (circular_buffer_is_read_ready(client->write_to_outside) == false) {
        cr_assert_eq(loop(zappy, true), false);
    }
    const char *res = circular_buffer_read(client->write_to_outside);
    cr_assert_str_eq(res, "[player,food linemate deraumere sibur mendiane phiras thystame,,food linemate deraumere sibur mendiane phiras thystame]\n");
}

Test(loop_cmd_ai_look_around, look_from_west_level_1)
{
    zappy_t *zappy = NULL;

    set_up_tests(&zappy, 1, 9025);
    ntw_client_t *client = L_DATA(zappy->ntw->clients->start);
    cr_assert_not_null(client);
    client_t *c = L_DATA(client);
    cr_assert_not_null(c);
    c->cl.ai.trantorien->x = 4;
    c->cl.ai.trantorien->y = 9;
    c->cl.ai.trantorien->level = 1;
    c->cl.ai.trantorien->direction = WEST;
    for (int i = 0; i < zappy->map->width * zappy->map->height; i++) {
        for (int j = 0; j < MAX_NB_RESOURCES; j++) {
            zappy->map->tiles[i].ressources[j] = (i % 2 == 0) ? 1 : 0;
        }
    }
    circular_buffer_write(client->read_from_outside, "Look\n");
    while (circular_buffer_is_read_ready(client->write_to_outside) == false) {
        cr_assert_eq(loop(zappy, true), false);
    }
    cr_assert_str_eq(circular_buffer_read(client->write_to_outside), "[food linemate deraumere sibur mendiane phiras thystame player,,,]\n");
}
