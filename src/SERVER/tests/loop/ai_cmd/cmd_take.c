#include <criterion/criterion.h>
#include <stdbool.h>

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

Test(loop_cmd_ai_take, basic)
{
    zappy_t *zappy = NULL;
    int last = 0;

    set_up_tests(&zappy, 1, 8081);
    ntw_client_t *client = L_DATA(zappy->ntw->clients->start);
    cr_assert_not_null(client);
    zappy->map->tiles[0].ressources[FOOD] += 1;
    client_t *c = L_DATA(client);
    cr_assert_not_null(c);
    c->cl.ai.trantorien->x = 0;
    c->cl.ai.trantorien->y = 0;
    last = c->cl.ai.trantorien->ressources[FOOD];
    printf("---------------------------------\n");
    circular_buffer_write(client->read_from_outside, "Take food\n");
    printf("-------- ABC TEST ---------------\n");
    while (circular_buffer_is_read_ready(client->write_to_outside) == false) {
        printf("--------------------------------- dededede --------------\n");
        cr_assert_eq(loop(zappy, true), false);
        printf("--------------------------------- fffffff --------------\n");
    }
    printf("------------test ets test--------\n");
    cr_assert_str_eq(circular_buffer_read(client->write_to_outside), "ok\n");
    cr_assert_eq(c->cl.ai.trantorien->ressources[FOOD], last + 1);
}

Test(loop_cmd_ai_take, no_food)
{
    zappy_t *zappy = NULL;
    int last = 0;

    set_up_tests(&zappy, 1, 8082);
    ntw_client_t *client = L_DATA(zappy->ntw->clients->start);
    cr_assert_not_null(client);
    zappy->map->tiles[0].ressources[FOOD] = 0;
    client_t *c = L_DATA(client);
    cr_assert_not_null(c);
    c->cl.ai.trantorien->x = 0;
    c->cl.ai.trantorien->y = 0;
    last = c->cl.ai.trantorien->ressources[FOOD];
    printf("---------------------------------\n");
    circular_buffer_write(client->read_from_outside, "Take food\n");
    printf("-------- ABC TEST ---------------\n");
    while (circular_buffer_is_read_ready(client->write_to_outside) == false) {
        printf("--------------------------------- dededede --------------\n");
        cr_assert_eq(loop(zappy, true), false);
        printf("--------------------------------- fffffff --------------\n");
    }
    printf("------------test ets test--------\n");
    cr_assert_str_eq(circular_buffer_read(client->write_to_outside), "ko\n");
    cr_assert_eq(c->cl.ai.trantorien->ressources[FOOD], last);
}
