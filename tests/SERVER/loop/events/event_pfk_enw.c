/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** event_pfk_enw
*/

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
    list_append(args.teams_name, "Team1", NULL, NULL);
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

Test(loop_event_pfk, basic_pfk)
{
    zappy_t *zappy = NULL;
    ntw_client_t *graph = NULL;
    char res[512] = {0};

    set_up_tests(&zappy, 1, 9410, &graph);
    ntw_client_t *client_e = L_DATA(zappy->ntw->clients->start);
    cr_assert_not_null(client_e);
    client_t *c_e = L_DATA(client_e);
    cr_assert_not_null(c_e);
    circular_buffer_write(client_e->read_from_outside, "Fork\n");
    while (circular_buffer_is_read_ready(client_e->write_to_outside) == false) {
        cr_assert_eq(loop(zappy, true), false);
    }
    snprintf(res, 511, "pfk %d\n", c_e->cl.ai.trantorien->id);
    cr_assert_str_eq(circular_buffer_read(graph->write_to_outside), res);
}

Test(loop_event_pfk, basic_pfk_and_enw)
{
    zappy_t *zappy = NULL;
    ntw_client_t *graph = NULL;
    char res[512] = {0};

    set_up_tests(&zappy, 1, 9411, &graph);
    ntw_client_t *client_e = L_DATA(zappy->ntw->clients->start);
    cr_assert_not_null(client_e);
    client_t *c_e = L_DATA(client_e);
    cr_assert_not_null(c_e);
    zappy->map->tiles[0].ressources[LINEMATE] = 1;
    zappy->map->tiles[0].ressources[DERAUMERE] = 1;
    zappy->map->tiles[0].ressources[SIBUR] = 1;
    c_e->cl.ai.trantorien->ressources[FOOD] = 20;
    c_e->cl.ai.trantorien->x = 0;
    c_e->cl.ai.trantorien->y = 0;
    c_e->cl.ai.trantorien->level = 2;
    circular_buffer_write(client_e->read_from_outside, "Fork\n");
    while (circular_buffer_is_read_ready(client_e->write_to_outside) == false) {
        cr_assert_eq(loop(zappy, true), false);
    }
    memset(res, 0, 512);
    snprintf(res, 511, "pfk %d\n", c_e->cl.ai.trantorien->id);
    cr_assert_str_eq(circular_buffer_read(graph->write_to_outside), res);
    trantorien_t *trantorien = L_DATA(zappy->trantoriens_available->end);
    cr_assert_not_null(trantorien);
    memset(res, 0, 512);
    snprintf(res, 511, "enw %d %d %d %d\n", trantorien->id, c_e->cl.ai.trantorien->id, trantorien->x, trantorien->y);
    cr_assert_str_eq(circular_buffer_read(graph->write_to_outside), res);
}
