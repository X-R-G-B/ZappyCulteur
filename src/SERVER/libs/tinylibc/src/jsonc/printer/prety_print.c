/*
** EPITECH PROJECT, 2022
** libjson
** File description:
** prety print a any_t json
*/

#include <stddef.h>
#include "tlcdico.h"
#include "tlcjson.h"
#include "tlcllists.h"
#include "tlcstdios.h"

int do_print_dico(int fd, any_t *any, int indent);
int do_print_array(int fd, any_t *any, int indent);
int do_print_string(int fd, any_t *any, int indent);
int do_print_number(int fd, any_t *any, int indent);

int prety_print_rec(int fd, any_t *any, int indent)
{
    int nb = 0;
    int (*do_print_funcs[])(int, any_t *, int) = {do_print_string,
    do_print_number, do_print_number, do_print_array, do_print_dico};

    if (any == NULL) {
        return 0;
    }
    nb += do_print_funcs[any->type](fd, any, indent);
    return (nb);
}

int prety_print(any_t *any, int fd)
{
    int ret = 0;

    if (any == NULL) {
        return (0);
    }
    ret = prety_print_rec(fd, any, 4);
    x_putcd(fd, '\n', false);
    return ret;
}
