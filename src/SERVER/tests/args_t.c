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

Test(args, args_bad_port)
{
    const char *av[] = {"bin_test", "-p", "-4040", "-x", "15", "-y", "20", "-n", "abc", "def", "-c", "1", "-f", "1", NULL};
    args_t *args = args_init(14, av);

    if (args != NULL) {
        cr_assert(args->is_ok == false, "Invalid arguments");
    } else {
        cr_assert_null(args);
    }
}

Test(args, args_bad_with)
{
    const char *av[] = {"bin_test", "-p", "4040", "-x", "-15", "-y", "20", "-n", "abc", "def", "-c", "1", "-f", "1", NULL};
    args_t *args = args_init(14, av);

    if (args != NULL) {
        cr_assert(args->is_ok == false, "Invalid arguments");
    } else {
        cr_assert_null(args);
    }
}

Test(args, args_bad_height)
{
    const char *av[] = {"bin_test", "-p", "4040", "-x", "15", "-y", "-20", "-n", "abc", "def", "-c", "1", "-f", "1", NULL};
    args_t *args = args_init(14, av);

    if (args != NULL) {
        cr_assert(args->is_ok == false, "Invalid arguments");
    } else {
        cr_assert_null(args);
    }
}

Test(args, args_bad_freq)
{
    const char *av[] = {"bin_test", "-p", "4040", "-x", "15", "-y", "20", "-n", "abc", "def", "-c", "1", "-f", "-1", NULL};
    args_t *args = args_init(14, av);

    if (args != NULL) {
        cr_assert(args->is_ok == false, "Invalid arguments");
    } else {
        cr_assert_null(args);
    }
}

Test(args, args_bad_clients_per_teams)
{
    const char *av[] = {"bin_test", "-p", "4040", "-x", "15", "-y", "20", "-n", "abc", "def", "-c", "-1", "-f", "1", NULL};
    args_t *args = args_init(14, av);

    if (args != NULL) {
        cr_assert(args->is_ok == false, "Invalid arguments");
    } else {
        cr_assert_null(args);
    }
}

Test(args, args_bad_max_freq)
{
    const char *av[] = {"bin_test", "-p", "4040", "-x", "15", "-y", "20", "-n", "abc", "def", "-c", "1", "-f", "0", NULL};
    args_t *args = args_init(14, av);

    if (args != NULL) {
        cr_assert(args->is_ok == false, "Invalid arguments");
    } else {
        cr_assert_null(args);
    }
}

Test(args, args_no_enough_args_1)
{
    const char *av[] = {"bin_test", "-p", "4040", "-x", "15", "-y", "20", "-n", "abc", "-c", "1", "-f", "1", NULL};
    args_t *args = args_init(13, av);

    if (args != NULL) {
        cr_assert(args->is_ok == false, "Invalid arguments");
    } else {
        cr_assert_null(args);
    }
}

Test(args, args_no_enough_args_2)
{
    const char *av[] = {"bin_test", "-p", "4040", "-x", "15", "-y", "20", "-c", "1", "-f", "1", NULL};
    args_t *args = args_init(11, av);

    if (args != NULL) {
        cr_assert(args->is_ok == false, "Invalid arguments");
    } else {
        cr_assert_null(args);
    }
}

Test(args, args_no_enough_args_3)
{
    const char *av[] = {"bin_test", "-p", "4040", "-x", "15", "-y", "20", "-n", "abc", "-f", "1", NULL};
    args_t *args = args_init(11, av);

    if (args != NULL) {
        cr_assert(args->is_ok == false, "Invalid arguments");
    } else {
        cr_assert_null(args);
    }
}

Test(args, args_no_enough_args_4)
{
    const char *av[] = {"bin_test", "-p", "4040", "-x", "15", "-y", "20", "-n", "abc", "-c", "1", NULL};
    args_t *args = args_init(11, av);

    if (args != NULL) {
        cr_assert(args->is_ok == false, "Invalid arguments");
    } else {
        cr_assert_null(args);
    }
}

Test(args, args_no_enough_args_5)
{
    const char *av[] = {"bin_test", "-p", "4040", "-x", "15", "-y", "20", "-c", "1", NULL};
    args_t *args = args_init(9, av);

    if (args != NULL) {
        cr_assert(args->is_ok == false, "Invalid arguments");
    } else {
        cr_assert_null(args);
    }
}

Test(args, args_no_enough_args_6)
{
    const char *av[] = {"bin_test", "-p", "4040", "-x", "15", "-y", "20", "-f", "1", NULL};
    args_t *args = args_init(9, av);

    if (args != NULL) {
        cr_assert(args->is_ok == false, "Invalid arguments");
    } else {
        cr_assert_null(args);
    }
}

Test(args, args_no_enough_args_7)
{
    const char *av[] = {"bin_test", "-p", "4040", "-x", "15", "-y", "20", "-n", "abc", NULL};
    args_t *args = args_init(9, av);

    if (args != NULL) {
        cr_assert(args->is_ok == false, "Invalid arguments");
    } else {
        cr_assert_null(args);
    }
}

Test(args, args_no_enough_args_8)
{
    const char *av[] = {"bin_test", "-p", "4040", "-x", "15", "-y", "20", NULL};
    args_t *args = args_init(7, av);

    if (args != NULL) {
        cr_assert(args->is_ok == false, "Invalid arguments");
    } else {
        cr_assert_null(args);
    }
}

Test(args, arg_wrong_arg_1)
{
    const char *av[] = {"bin_test", "-p", "4040", "-x", "15", "-y", "20", "-n", "abc", "-c", "1", "-f", "1", "-z", "1", NULL};
    args_t *args = args_init(15, av);

    if (args != NULL) {
        cr_assert(args->is_ok == false, "Invalid arguments");
    } else {
        cr_assert_null(args);
    }

}

Test(args, args_wrong_arg_2)
{
    const char *av[] = {"bin_test", "-p", "4040", "-x", "15", "-y", "20", "-n", "abc", "-c", "1", "-f", "1", "-z", "1", NULL};
    args_t *args = args_init(15, av);

    if (args != NULL) {
        cr_assert(args->is_ok == false, "Invalid arguments");
    } else {
        cr_assert_null(args);
    }
}

Test(args, args_wrong_arg_3)
{
    const char *av[] = {"bin_test", "-p", "4040", "-x", "15", "-y", "20", "-n", "abc", "-c", "1", "-f", "1", "-z", "1", NULL};
    args_t *args = args_init(15, av);

    if (args != NULL) {
        cr_assert(args->is_ok == false, "Invalid arguments");
    } else {
        cr_assert_null(args);
    }
}

Test(args, args_wrong_arg_4)
{
    const char *av[] = {"bin_test", "-p", "4040", "-x", "15", "-y", "20", "-n", "abc", "-c", "1", "-f", "1", "-z", "1", NULL};
    args_t *args = args_init(15, av);

    if (args != NULL) {
        cr_assert(args->is_ok == false, "Invalid arguments");
    } else {
        cr_assert_null(args);
    }
}
