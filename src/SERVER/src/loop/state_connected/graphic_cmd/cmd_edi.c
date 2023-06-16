/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** cmd_edi
*/

#include <stdbool.h>
#include <stdio.h>
#include "ntw.h"
#include "map.h"
#include "internal.h"
#include "client.h"

bool cmd_edi(ntw_t *ntw, ntw_client_t *cl)
{
    client_t *client = NULL;
    char buff[512] = {0};

    if (ntw == NULL || cl == NULL) {
        return false;
    }
    client = L_DATA(cl);
    if (client == NULL) {
        return false;
    }
    snprintf(buff, 511, "edi %d\n", client->id);
    circular_buffer_write(cl->write_to_outside, buff);
    return true;
}
