/*
** EPITECH PROJECT, 2023
** zappy server zappy
** File description:
** find trantorien by id
*/

#include "tlcllists.h"
#include "zappy.h"
#include "trantorien.h"
#include "client.h"

trantorien_t *zappy_trantorien_find_by_id(zappy_t *zappy, int id)
{
    trantorien_t *trantorien = NULL;
    ntw_client_t *cl = NULL;
    client_t *cc = NULL;

    for (L_EACH(client, zappy->ntw->clients)) {
        cl = L_DATA(client);
        cc = (cl == NULL) ? NULL : cl->data;
        if (cc == NULL) {
            continue;
        }
        if (cc->type != AI) {
            continue;
        }
        if (cc->id == id && cc->cl.ai.trantorien != NULL) {
            trantorien = cc->cl.ai.trantorien;
            break;
        }
    }
    return trantorien;
}
