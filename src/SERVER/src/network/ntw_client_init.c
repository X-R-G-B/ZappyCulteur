/*
** EPITECH PROJECT, 2023
** zappy server ntw
** File description:
** client init
*/

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "circular_buffer.h"
#include "ntw.h"

static bool init_circulars(ntw_client_t *cl)
{
    cl->read_from_outside = circular_buffer_create("\n");
    if (cl->read_from_outside == NULL) {
        return false;
    }
    cl->write_to_outside = circular_buffer_create("\n");
    if (cl->write_to_outside == NULL) {
        circular_buffer_destroy(cl->read_from_outside);
        cl->read_from_outside = NULL;
        return false;
    }
    return true;
}

ntw_client_t *ntw_client_init(int fd)
{
    ntw_client_t *cl = NULL;

    if (fd < 0) {
        return NULL;
    }
    cl = malloc(sizeof(ntw_client_t));
    if (cl == NULL) {
        return NULL;
    }
    memset(cl, 0, sizeof(ntw_client_t));
    cl->fd = fd;
    if (init_circulars(cl) == false) {
        ntw_client_destroy(cl);
        return NULL;
    }
    return cl;
}
