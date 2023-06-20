/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** zappy_check_end
*/

#include <stdbool.h>
#include "tlcstrings.h"
#include "client.h"
#include "broadcast_events.h"
#include "zappy.h"


static bool is_an_existing_team(list_t *teams, char *team_name)
{
    char *team = NULL;

    for (L_EACH(data, teams)) {
        team = L_DATA(data);
        if (team == NULL) {
            continue;
        }
        if (x_strcmp(team, team_name) == 0) {
            return true;
        }
    }
    return false;
}

static bool check_egg_end(client_t *client, list_t *tr_available)
{
    trantorien_t *tr = NULL;
    char *last_team = NULL;

    if (client == NULL) {
        if (tr_available->len == 0)
            return true;
        else
            return false;
    }
    last_team = client->cl.ai.trantorien->team_name;
    for (L_EACH(data, tr_available)) {
        tr = L_DATA(data);
        if (tr == NULL || tr->team_name == NULL) {
            continue;
        }
        if (x_strcmp(tr->team_name, last_team) != 0) {
            return false;
        }
    }
    return true;
}

static bool check_team_end(zappy_t *zappy)
{
    client_t *cl = NULL;
    list_t *teams = list_create();

    for (L_EACH(data, zappy->ntw->clients)) {
        cl = L_DATA(L_DATAT(ntw_client_t *, data));
        if (cl == NULL || cl->type != AI || cl->cl.ai.trantorien == NULL) {
            continue;
        }
        if (cl->cl.ai.trantorien->alive == true && is_an_existing_team(teams,
            cl->cl.ai.trantorien->team_name) == false) {
            list_append(teams, cl, NULL, NULL);
        }
    }
    if (teams->len <= 1 && check_egg_end(L_DATA(teams->start),
        zappy->trantoriens_available) == true) {
        cmd_seg(zappy->ntw, L_DATA(teams->start));
        return true;
    } else {
        return false;
    }
}

static bool check_win(zappy_t *zappy)
{
    client_t *cl = NULL;

    for (L_EACH(data, zappy->ntw->clients)) {
        cl = L_DATA(L_DATAT(ntw_client_t *, data));
        if (cl == NULL || cl->type != AI || cl->cl.ai.trantorien == NULL) {
            continue;
        }
        if (cl->cl.ai.trantorien->alive == true
                && cl->cl.ai.trantorien->level == LVL_MAX) {
            cmd_seg(zappy->ntw, cl);
            return true;
        }
    }
    return false;
}

bool check_end(zappy_t *zappy, bool is_end)
{
    if (is_end == false || zappy->is_end) {
        return false;
    }
    if (check_win(zappy) == true || check_team_end(zappy) == true) {
        zappy->is_end = true;
        return false;
    }
    return true;
}
