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

Test(args, bad_port)
{
    const char *av[] = {"bin_test", "-p", "abc", "-x", "15", "-y", "20", "-n", "abc", "def", "-c", "1", "-f", "1", NULL};
    args_t *args = args_init(14, av);
    if (args != NULL && args->is_ok != false) {
        cr_assert_null(args);
    }
    args_destroy(args);
}

Test(args, bad_freq)
{
    const char *av[] = {"bin_test", "-p", "4040", "-x", "15", "-y", "20", "-n", "abc", "def", "-c", "abc", "-f", "a", NULL};
    args_t *args = args_init(14, av);
    if (args != NULL && args->is_ok != false) {
        cr_assert_null(args);
    }
    args_destroy(args);
}

Test(args, bad_width)
{
    const char *av[] = {"bin_test", "-p", "4040", "-x", "abc", "-y", "20", "-n", "abc", "def", "-c", "1", "-f", "1", NULL};
    args_t *args = args_init(14, av);
    if (args != NULL && args->is_ok != false) {
        cr_assert_null(args);
    }
    args_destroy(args);
}

Test(args, bad_height)
{
    const char *av[] = {"bin_test", "-p", "4040", "-x", "15", "-y", "abc", "-n", "abc", "def", "-c", "1", "-f", "1", NULL};
    args_t *args = args_init(14, av);
    if (args != NULL && args->is_ok != false) {
        cr_assert_null(args);
    }
    args_destroy(args);
}

Test(args, bad_name)
{
    const char *av[] = {"bin_test", "-p", "4040", "-x", "15", "-y", "20", "-n", "-c", "1", "-f", "1", NULL};
    args_t *args = args_init(14, av);
    if (args != NULL && args->is_ok != false) {
        cr_assert_null(args);
    }
    args_destroy(args);
}

Test(args, bad_c)
{
    const char *av[] = {"bin_test", "-p", "4040", "-x", "15", "-y", "20", "-n", "abc", "-c", "abc", "-f", "1", NULL};
    args_t *args = args_init(13, av);
    if (args != NULL && args->is_ok != false) {
        cr_assert_null(args);
    }
    args_destroy(args);
}

Test(args, bad_param)
{
    const char *av[] = {"bin_test", "-p", "-x", "15", "-y", "20", "-n", "abc", "-c", "1", "-f", "1", NULL};
    args_t *args = args_init(13, av);
    if (args != NULL && args->is_ok != false) {
        cr_assert_null(args);
    }
    args_destroy(args);
}

Test(args, bad_param1)
{
    const char *av[] = {"bin_test", "-p", "4040", "-x", "-y", "20", "-n", "abc", "-c", "1", "-f", "1", NULL};
    args_t *args = args_init(13, av);
    if (args != NULL && args->is_ok != false) {
        cr_assert_null(args);
    }
    args_destroy(args);
}

Test(args, bad_param2)
{
    const char *av[] = {"bin_test", "-p", "4040", "-x", "15", "-y", "-n", "abc", "-c", "1", "-f", "1", NULL};
    args_t *args = args_init(13, av);
    if (args != NULL && args->is_ok != false) {
        cr_assert_null(args);
    }
    args_destroy(args);
}

Test(args, bad_param3)
{
    const char *av[] = {"bin_test", "-p", "4040", "-x", "15", "-y", "20", "-n", "-c", "1", "-f", "1", NULL};
    args_t *args = args_init(13, av);
    if (args != NULL && args->is_ok != false) {
        cr_assert_null(args);
    }
    args_destroy(args);
}

Test(args, bad_param4)
{
    const char *av[] = {"bin_test", "-p", "4040", "-x", "15", "-y", "20", "-n", "abc", "-c", "-f", "1", NULL};
    args_t *args = args_init(13, av);
    if (args != NULL && args->is_ok != false) {
        cr_assert_null(args);
    }
    args_destroy(args);
}

Test(args, bad_param5)
{
    const char *av[] = {"bin_test", "-p", "4040", "-x", "15", "-y", "20", "-n", "abc", "-c", "1", "-f", NULL};
    args_t *args = args_init(13, av);
    if (args != NULL && args->is_ok != false) {
        cr_assert_null(args);
    }
    args_destroy(args);
}
