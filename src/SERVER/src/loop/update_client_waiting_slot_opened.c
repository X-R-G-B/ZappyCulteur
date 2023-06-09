/*
** EPITECH PROJECT, 2023
** zappy server loop
** File description:
** update waiting slot opened
*/

#include <stdbool.h>
#include "client.h"
#include "internal.h"
#include "trantorien.h"

bool update_client_waiting_slot_opened(zappy_t *zappy, ntw_client_t *cl)
{
    client_t *client;

    if (cl == NULL || zappy == NULL || cl->data == NULL) {
        return true;
    }
    client = cl->data;
    if (add_client_to_trantorien(client,
            zappy->trantoriens_available) == false) {
        return true;
    }
    client->state = CONNECTED;
    client->type = AI;
    send_id(client, cl);
    send_size(zappy->args, cl);
    client->cl.ai.trantorien->id = client->id;
    return true;
}