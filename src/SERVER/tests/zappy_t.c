/*
** EPITECH PROJECT, 2023
** test
** File description:
** test
*/

#include <criterion/criterion.h>
#include <criterion/internal/assert.h>
#include <stdbool.h>
#include <signal.h>
#include "args.h"
#include "tlcllists.h"
#include "zappy.h"

Test(zappy_t, init_destroy)
{
    zappy_t *zappy = NULL;
    args_t args = {
        .clients_per_teams = 1,
        .teams_name = list_create(),
        .freq = 1,
        .height = 10,
        .width = 10,
        .is_ok = true,
        .port = 4040,
    };

    zappy = zappy_init(&args);
    cr_assert_not_null(zappy);
    zappy_destroy(zappy);
}

Test(zappy_t, init_destroy_check)
{
    zappy_t *zappy = NULL;
    args_t args = {
        .clients_per_teams = 1,
        .teams_name = list_create(),
        .freq = 1,
        .height = 10,
        .width = 15,
        .is_ok = true,
        .port = 4040,
    };

    zappy = zappy_init(&args);
    cr_assert_not_null(zappy);
    cr_assert_eq(zappy->map->height, 10);
    cr_assert_eq(zappy->map->width, 15);
    cr_assert_not_null(zappy->ntw);
    zappy_destroy(zappy);
}
