/*
** EPITECH PROJECT, 2023
** zappy server global
** File description:
** on new connection
*/

#include "client.h"
#include "ntw.h"
#include "zappy.h"

void on_new_conn(ntw_client_t *new_client)
{
    new_client->data = client_init();
    new_client->on_delete = (void (*)(void *)) client_destroy;
}
