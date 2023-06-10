/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** trantorien_add_client
*/

#include <string.h>
#include "trantorien.h"
#include "client.h"
#include "tlcllists.h"

bool add_client_to_trantorien(client_t *cc, list_t *trantoriens_available)
{
    trantorien_t *trantorien = NULL;

    if (cc == NULL || trantoriens_available == NULL) {
        return false;
    }
    for (L_EACH(data, trantoriens_available)) {
        trantorien = L_DATAT(trantorien_t *, data);
        if (trantorien == NULL || trantorien->team_name == NULL
                || strcmp(trantorien->team_name, cc->name) != 0) {
            continue;
        }
        cc->cl.ai.trantorien = trantorien;
        data->data = NULL;
        return true;
    }
    return false;
}
