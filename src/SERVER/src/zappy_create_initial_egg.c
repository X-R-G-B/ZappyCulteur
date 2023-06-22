/*
** EPITECH PROJECT, 2023
** zappy server
** File description:
** create initial egg
*/

#include <stdbool.h>
#include "tlcllists.h"
#include "zappy.h"
#include "trantorien.h"

static bool add_trantorien_team(list_t *list, const char *team_name,
    args_t *args)
{
    trantorien_t *trantorien = NULL;

    for (int i = 0; i < args->clients_per_teams; i++) {
        trantorien = trantorien_init(team_name, args->width, args->height);
        trantorien->id = get_id();
        if (trantorien == NULL) {
            return false;
        }
        list_append(list, trantorien, (void (*)(void *)) trantorien_destroy,
            NULL);
    }
    return true;
}

list_t *zappy_create_initial_egg(args_t *args)
{
    list_t *list = NULL;
    bool status = true;

    if (args == NULL) {
        return NULL;
    }
    list = list_create();
    if (list == NULL) {
        return NULL;
    }
    for (L_EACH(name, args->teams_name)) {
        status = status && add_trantorien_team(list, name->data, args);
    }
    if (status == false) {
        list_delete(list);
        return NULL;
    }
    return list;
}
