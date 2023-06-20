/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** command_take_object
*/

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "circular_buffer.h"
#include "command_reponses.h"
#include "ntw.h"
#include "tlcllists.h"
#include "zappy.h"
#include "trantorien.h"
#include "map.h"
#include "client.h"
#include "internal.h"
#include "broadcast_events.h"

/*   -0.5    0.5
|  -1  |  +0  |  +1  |
|------|------|------|------
|   0  |   1  |   2  |  -1
|------x------x------|------ -0.5
|   7  |  xx  |   3  |  +0
|------x------x------|------ 0.5
|   6  |   5  |   4  |  +1
|------|------|------|------
static const int direction_to_follow[DIR_SIZE][2] = {
    {-1, -1},
    {-1, 0},
    {-1, 1},
    {1, 0},
    {1, 1},
    {0, 1},
    {-1, 1},
    {-1, 0}
};
{x, y, size_x, size_y}
*/
static const float dir_check_sup[DIR_SIZE][4] = {
    {-0.5, -0.5, -1, -1},
    {0.5, -0.5, -1, -1},
    {0.5, -0.5, 1, -1},
    {0.5, -0.5, 1, 1},
    {0.5, 0.5, 1, 1},
    {0.5, 0.5, -1, 1},
    {-0.5, 0.5, -1, 1},
    {-0.5, -0.5, -1, 1}
};

static int get_pos_vect_rel(int dest, int start, int map_len)
{
    int res = dest - start;

    if (res > map_len / 2) {
        res = map_len - res;
        res *= -1;
    }
    return res;
}

static int get_rect_num_abs(float vec_norm[2])
{
    float pos_sq[2] = {0};
    float size_sq[2] = {0};

    for (int i = 0; i < DIR_SIZE; i++) {
        pos_sq[0] = dir_check_sup[i][0];
        pos_sq[1] = dir_check_sup[i][1];
        size_sq[0] = dir_check_sup[i][2];
        size_sq[1] = dir_check_sup[i][3];
        if (is_in_box(vec_norm, pos_sq, size_sq) == true) {
            return i + 1;
        }
    }
    return -1;
}

static void calculate_send_broadcast(int trnt_x, int trnt_y,
    ntw_client_t *trnt, const char *msg)
{
    client_t *cl = trnt->data;
    trantorien_t *trantor = cl->cl.ai.trantorien;
    float vec[2] = {0};
    float dist = 0;
    int pos = 0;

    if (trantor->x != trnt_x || trantor->y != trnt_y) {
        vec[0] = get_pos_vect_rel(trnt_x, trantor->x, cl->width);
        vec[1] = get_pos_vect_rel(trnt_y, trantor->y, cl->height);
        dist = sqrt(vec[0] * vec[0] + vec[1] * vec[1]);
        vec[0] = vec[0] / dist;
        vec[1] = vec[1] / dist;
        pos = get_rect_num_abs(vec);
    }
    if (0 <= pos && pos <= DIR_SIZE) {
        send_broadcast_pos(trnt, pos, msg);
    }
}

static void spread_broadcast(trantorien_t *trnt, zappy_t *zappy,
    const char *msg)
{
    ntw_client_t *ncl = NULL;

    for (L_EACH(node, zappy->ntw->clients)) {
        ncl = L_DATA(node);
        if (ncl == NULL || ncl->data == NULL ||
                L_DATAT(client_t *, ncl)->type != AI ||
                L_DATAT(client_t *, ncl)->cl.ai.trantorien == NULL ||
                L_DATAT(client_t *, ncl)->cl.ai.trantorien == trnt) {
            continue;
        }
        calculate_send_broadcast(trnt->x, trnt->y, ncl, msg);
    }
}

int command_broadcast(trantorien_t *trnt, zappy_t *zappy,
    ntw_client_t *cl, action_t *action)
{
    if (trnt == NULL || zappy == NULL || cl == NULL || action == NULL) {
        return EXIT_FAILURE;
    }
    spread_broadcast(trnt, zappy, action->param.broadcast_msg);
    cmd_pbc(zappy->ntw, cl, action);
    circular_buffer_write(cl->write_to_outside, OK_RESPONSE);
    return EXIT_SUCCESS;
}
