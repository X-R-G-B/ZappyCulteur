#include <stdbool.h>
#include <stdio.h>
#include "ntw.h"
#include "client.h"
#include "trantorien.h"
#include "zappy.h"

static const char *format_error_too_many_level = "Incantation: too many "
                                        "trantoriens at level %d"
                                        "initial trantorien ID: %d\n";

static const char *format_error_too_less_level = "Incantation: too less "
                                        "trantoriens at level %d; "
                                        "initial trantorien ID: %d\n";

static const char *format_error_resource = "Incantation: too less "
                                            "resources of %d (on case: %d); "
                                            "initial trantorien ID: %d\n";

static const char *format_error_err = "Incantation: error; "
                                    "initial trantorien ID: %d\n";

static const int nb_level_players[LVL_MAX - 1] = {
    1, 2, 2, 4, 4, 6, 6
};

static void print_debug_error(int nb_tr_case, int lvl, int id)
{
    if (nb_tr_case < nb_level_players[lvl - 1]) {
        fprintf(stderr, format_error_too_less_level, lvl, id);
    } else if (nb_tr_case > nb_level_players[lvl - 1]) {
        fprintf(stderr, format_error_too_many_level, lvl, id);
    }
}

static bool check_incantation_lvl_availability(trantorien_t *ref_tr,
    ntw_t *ntw)
{
    int nb_trantorien_lvl = 0;
    int ref_tr_lvl = ref_tr->level;
    client_t *cl = NULL;
    trantorien_t *tr = NULL;

    for (L_EACH(client, ntw->clients)) {
        cl = L_DATA(L_DATAT(ntw_client_t *, client));
        if (cl == NULL || cl->type != AI || cl->cl.ai.trantorien == NULL) {
            continue;
        }
        tr = cl->cl.ai.trantorien;
        if (tr->level == ref_tr_lvl && ref_tr->x == tr->x &&
                ref_tr->y == tr->y) {
            nb_trantorien_lvl += 1;
        }
    }
    print_debug_error(nb_trantorien_lvl, ref_tr_lvl, ref_tr->id);
    return (nb_trantorien_lvl == nb_level_players[ref_tr_lvl - 1]);
}

bool check_incantation_availability(trantorien_t *trantorien, map_t *map,
    ntw_t *ntw)
{
    int map_i = 0;

    if (trantorien == NULL || map == NULL || ntw == NULL) {
        fprintf(stderr, format_error_err, trantorien->id);
        return false;
    }
    map_index_x_y_to_i(map, trantorien->x, trantorien->y, &map_i);
    for (int i = FOOD; i < PLAYER; i++) {
        if (map->tiles[map_i].ressources[i + LINEMATE] <
                level_ressources[trantorien->level - 1][i]) {
            fprintf(stderr, format_error_resource, i + LINEMATE,
                map->tiles[map_i].ressources[i + LINEMATE], trantorien->id);
            return false;
        }
    }
    if (check_incantation_lvl_availability(trantorien, ntw) == false) {
        return false;
    }
    return true;
}
