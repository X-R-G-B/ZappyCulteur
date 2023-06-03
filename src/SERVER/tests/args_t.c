/*
** EPITECH PROJECT, 2023
** test
** File description:
** test
*/

#include <criterion/criterion.h>
#include "args.h"
#include "tlcllists.h"

Test(args, args_init)
{
    const char *av[] = {"bin_test", "-p", "4040", "-x", "15", "-y", "20", "-n", "abc", "def", "-c", "1", "-f", "1", NULL};
    args_t *args = args_init(14, av);
    const char *rep[] = {"abc", "def"};
    int i = 0;

    cr_assert_not_null(args);
    cr_assert_eq(args->port, 4040);
    cr_assert_eq(args->width, 15);
    cr_assert_eq(args->height, 20);
    cr_assert_eq(args->freq, 1);
    for (L_EACH(s, args->teams_name)) {
        cr_assert_str_eq(L_DATA(s), rep[i]);
        i++;
    }
    args_destroy(args);
}
