/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** event_seg
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
        .clients_per_teams = 0,
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
        strcpy(c->name, "Team1");
        c->state = CONNECTED;
        c->type = AI;
        c->cl.ai.trantorien = trantorien_init("Team1", args.width, args.height);
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

Test(loop_event_seg, basic_alone)
{
    zappy_t *zappy = NULL;
    ntw_client_t *graph = NULL;
    char res[512] = {0};

    set_up_tests(&zappy, 2, 9500, &graph);
    ntw_client_t *client_e = L_DATA(zappy->ntw->clients->start);
    cr_assert_not_null(client_e);
    client_t *c_e = L_DATA(client_e);
    cr_assert_not_null(c_e);
    c_e->cl.ai.trantorien->ressources[FOOD] = 1;
    zappy->map->tiles[0].ressources[LINEMATE] = 1;
    c_e->cl.ai.trantorien->x = 0;
    c_e->cl.ai.trantorien->y = 0;
    circular_buffer_write(client_e->read_from_outside, "Incantation\n");
    while (circular_buffer_is_read_ready(client_e->write_to_outside) == false) {
        cr_assert_eq(loop(zappy, true), false);
    }
    cr_assert_str_eq(circular_buffer_read(client_e->write_to_outside), "Elevation underway\n");
    snprintf(res, 511, "pic %d %d %d %d\n", c_e->cl.ai.trantorien->x, c_e->cl.ai.trantorien->y, c_e->cl.ai.trantorien->level, c_e->cl.ai.trantorien->id);
    cr_assert_str_eq(circular_buffer_read(graph->write_to_outside), res);
    while (circular_buffer_is_read_ready(client_e->write_to_outside) == false) {
        cr_assert_eq(loop(zappy, true), false);
    }
    cr_assert_str_eq(circular_buffer_read(client_e->write_to_outside), "dead\n");
    memset(res, 0, 512);
    snprintf(res, 511, "pdi %d\n", c_e->cl.ai.trantorien->id);
    cr_assert_str_eq(circular_buffer_read(graph->write_to_outside), res);
    ntw_client_t *client_r = L_DATA(zappy->ntw->clients->start->next);
    cr_assert_not_null(client_r);
    cr_assert_eq(check_end(zappy, true), false);
    client_t *c_r = L_DATA(client_r);
    cr_assert_not_null(c_r);
    memset(res, 0, 512);
    snprintf(res, 511, "seg %s\n", c_r->cl.ai.trantorien->team_name);
    cr_assert_str_eq(circular_buffer_read(graph->write_to_outside), res);
}

static void set_up_tests_for_win(zappy_t **zappy, int nb_client, int port,
ntw_client_t **graphic)
{
    int j = 0;
    static args_t args = {
        .clients_per_teams = 0,
        .teams_name = NULL,
        .freq = 1000,
        .height = 10,
        .width = 10,
        .is_ok = true,
        .port = 0,
    };
    args.port = port;
    args.teams_name = list_create();
    list_append(args.teams_name, "Team1", NULL, NULL);
    list_append(args.teams_name, "Team2", NULL, NULL);
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
    for (L_EACH(x, (*zappy)->ntw->clients), j++) {
        ntw_client_t *client = L_DATA(x);
        client_t *c = L_DATA(client);

        cr_assert_not_null(c);
        c->id = get_id();
        strcpy(c->name, "Team1");
        c->state = CONNECTED;
        c->type = AI;
        c->cl.ai.trantorien = trantorien_init((j % 2 == 0) ? "Team1" : "Team2", args.width, args.height);
        c->cl.ai.trantorien->ressources[FOOD] = 9999;
        c->cl.ai.trantorien->id = c->id;
        c->cl.ai.trantorien->x = (j % 2 == 0) ? 0 : 2;
        c->cl.ai.trantorien->y = (j % 2 == 0) ? 0 : 2;
        c->cl.ai.trantorien->level = LVL_MAX - 1;
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

Test(loop_event_seg, basic_lvl_8)
{
    zappy_t *zappy = NULL;
    ntw_client_t *graph = NULL;
    char res[512] = {0};

    set_up_tests_for_win(&zappy, 12, 9500, &graph);
    ntw_client_t *client_e = L_DATA(zappy->ntw->clients->start);
    cr_assert_not_null(client_e);
    client_t *c_e = L_DATA(client_e);
    cr_assert_not_null(c_e);
    c_e->cl.ai.trantorien->level = LVL_MAX - 1;
    zappy->map->tiles[0].ressources[LINEMATE] = 2;
    zappy->map->tiles[0].ressources[DERAUMERE] = 2;
    zappy->map->tiles[0].ressources[SIBUR] = 2;
    zappy->map->tiles[0].ressources[MENDIANE] = 2;
    zappy->map->tiles[0].ressources[PHIRAS] = 2;
    zappy->map->tiles[0].ressources[THYSTAME] = 1;
    circular_buffer_write(client_e->read_from_outside, "Incantation\n");
    while (circular_buffer_is_read_ready(client_e->write_to_outside) == false) {
        cr_assert_eq(loop(zappy, true), false);
    }
    cr_assert_str_eq(circular_buffer_read(client_e->write_to_outside), "Elevation underway\n");
    snprintf(res, 511, "pic %d %d %d %d %d %d %d %d %d\n", c_e->cl.ai.trantorien->x, c_e->cl.ai.trantorien->y, c_e->cl.ai.trantorien->level, c_e->cl.ai.trantorien->id, 3, 5, 7, 9, 11);
    cr_assert_str_eq(circular_buffer_read(graph->write_to_outside), res);
    while (circular_buffer_is_read_ready(client_e->write_to_outside) == false) {
        cr_assert_eq(loop(zappy, true), false);
    }
    memset(res, 0, 512);
    snprintf(res, 511, "pie %d %d Current level:%d\n", c_e->cl.ai.trantorien->x, c_e->cl.ai.trantorien->y, c_e->cl.ai.trantorien->level);
    cr_assert_str_eq(circular_buffer_read(graph->write_to_outside), res);
    ntw_client_t *client_r = L_DATA(zappy->ntw->clients->start->next);
    cr_assert_not_null(client_r);
    cr_assert_eq(check_end(zappy, true), false);
    client_t *c_r = L_DATA(client_r);
    cr_assert_not_null(c_r);
    memset(res, 0, 512);
    snprintf(res, 511, "seg %s\n", c_e->cl.ai.trantorien->team_name);
    cr_assert_str_eq(circular_buffer_read(graph->write_to_outside), res);
}

static void set_up_tests_2_teams(zappy_t **zappy, int nb_client, int port,
ntw_client_t **graphic)
{
    int i = 0;
    static args_t args = {
        .clients_per_teams = 0,
        .teams_name = NULL,
        .freq = 1000,
        .height = 10,
        .width = 10,
        .is_ok = true,
        .port = 0,
    };
    args.port = port;
    args.teams_name = list_create();
    list_append(args.teams_name, "Team1", NULL, NULL);
    list_append(args.teams_name, "Team2", NULL, NULL);
    *zappy = zappy_init(&args);
    ntw_client_t *client;
    ntw_client_t *client_2;

    cr_assert_not_null(*zappy);
    cr_assert_not_null((*zappy)->map);
    cr_assert_not_null((*zappy)->map->tiles);
    for (int i = 0; i < nb_client; i++) {
        client = ntw_client_init(1);
        client_2 = ntw_client_init(1);

        list_append((*zappy)->ntw->clients, client, NULL, NULL);
        list_append((*zappy)->ntw->clients, client_2, NULL, NULL);
        (*zappy)->ntw->on_new_conn(client);
        (*zappy)->ntw->on_new_conn(client_2);
    }
    for (L_EACH(x, (*zappy)->ntw->clients), i++) {
        ntw_client_t *client = L_DATA(x);
        client_t *c = L_DATA(client);

        cr_assert_not_null(c);
        c->id = get_id();
        strcpy(c->name, "Team1");
        c->state = CONNECTED;
        c->type = AI;
        c->cl.ai.trantorien = trantorien_init((i % 2 == 0) ? "Team1" : "Team2", args.width, args.height);
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

Test(loop_event_no_seg, basic_no_seg_with_pex)
{
    zappy_t *zappy = NULL;
    ntw_client_t *graph = NULL;
    char res[512] = {0};

    set_up_tests_2_teams(&zappy, 2, 9402, &graph);
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
    c_r->cl.ai.trantorien->x = 0;
    c_r->cl.ai.trantorien->y = 0;
    circular_buffer_write(client_e->read_from_outside, "Eject\n");
    while (circular_buffer_is_read_ready(client_e->write_to_outside) == false) {
        cr_assert_eq(loop(zappy, true), false);
    }
    memset(res, 0, 512);
    snprintf(res, 511, "pex %d\n", c_r->cl.ai.trantorien->id);
    cr_assert_str_eq(circular_buffer_read(graph->write_to_outside), res);
    cr_assert_eq(check_end(zappy, true), true);
}
