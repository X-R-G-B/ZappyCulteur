/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** cmd_inventory
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

Test(loop_cmd_ai_inventory, inventory_cmd)
{
    zappy_t *zappy = NULL;
    int ressources[MAX_NB_TR_RESSOURCES] = {14, 0, 2, 3, 4, 5, 6};

    set_up_tests(&zappy, 1, 9101);
    ntw_client_t *client = L_DATA(zappy->ntw->clients->start);
    cr_assert_not_null(client);
    client_t *c = L_DATA(client);
    cr_assert_not_null(c);
    for (int i = 0; i < MAX_NB_TR_RESSOURCES; i++)
        c->cl.ai.trantorien->ressources[i] = ressources[i];
    circular_buffer_write(client->read_from_outside, "Inventory\n");
    while (circular_buffer_is_read_ready(client->write_to_outside) == false) {
        cr_assert_eq(loop(zappy, true), false);
    }
    char *str = circular_buffer_read(client->write_to_outside);
    cr_assert_not_null(str);
    cr_assert_str_eq(str, "[food 14, linemate 0, deraumere 2, sibur 3, mendiane 4, phiras 5, thystame 6]\n");
}
