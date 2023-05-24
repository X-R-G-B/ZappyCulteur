/*
** EPITECH PROJECT, 2022
** prety print
** File description:
** print dico
*/

#include <stdbool.h>
#include <stddef.h>
#include "tlcdico.h"
#include "tlcjson.h"
#include "tlcstdios.h"

int prety_print_rec(int fd, any_t *any, int indent);

static int close_dico(int fd, int indent, int nb, const dico_t *dict)
{
    for (int i = 0; dict->interns->start != NULL && i < indent - 4; i++) {
        nb += x_putcd(fd, ' ', false);
    }
    nb += x_putsd(fd, "}", false);
    return nb;
}

static int print_dico_key_value(int nb, int fd, int indent, node_t *elem)
{
    dico_node_t *node;

    if (elem == NULL) {
        return 0;
    }
    node = elem->data;
    nb += x_putcd(fd, '"', false);
    nb += x_putsd(fd, node->key, false);
    nb += x_putcd(fd, '"', false);
    nb += x_putsd(fd, ": ", false);
    nb += prety_print_rec(fd, node->value, indent + 4);
    return nb;
}

int do_print_dico(int fd, any_t *any, int indent)
{
    int nb = 0;
    node_t *elem = NULL;

    if (any == NULL || any->type != DICT) {
        return (0);
    }
    elem = any->value.dict->interns->start;
    nb += x_putsd(fd, "{", elem != NULL);
    do {
        for (int i = 0; elem != NULL && i < indent; i++) {
            nb += x_putcd(fd, ' ', false);
        }
        nb += print_dico_key_value(nb, fd, indent, elem);
        if ((elem == NULL) ? false : elem->next != NULL) {
            nb += x_putcd(fd, ',', false);
        }
        nb += (elem == NULL) ? 0 : x_putcd(fd, '\n', false);
        elem = (elem == NULL) ? NULL : elem->next;
    } while (elem != NULL);
    return close_dico(fd, indent, nb, any->value.dict);
}
