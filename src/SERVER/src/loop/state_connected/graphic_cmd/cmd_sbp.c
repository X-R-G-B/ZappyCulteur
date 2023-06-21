/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** cmd_sbp
*/

#include <stdbool.h>
#include <stdio.h>
#include "ntw.h"
#include "map.h"
#include "internal.h"
#include "client.h"

bool cmd_sbp(ntw_client_t *cl)
{
    if (cl == NULL) {
        return false;
    }
    circular_buffer_write(cl->write_to_outside, "sbp\n");
    return true;
}
