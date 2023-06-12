/*
** EPITECH PROJECT, 2023
** zappy server trantorien command broadcast
** File description:
** send
*/

#include <stdio.h>
#include "client.h"
#include "ntw.h"
#include "circular_buffer.h"
#include "tlcllists.h"
#include "trantorien.h"

/*
abs:
|------|------|------|
|   1  |   2  |   3  |
|------x------x------|
|   8  |  xx  |   4  |
|------x------x------|
|   7  |   6  |   5  |
|------|------|------|

relatif dir north(1):
|------|------|------|
|   8  |   1  |   2  |
|------x------x------|
|   7  |  xx  |   3  |
|------x------x------|
|   6  |   5  |   4  |
|------|------|------|
relatif dir east(2):
|------|------|------|
|   6  |   7  |   8  |
|------x------x------|
|   5  |  xx  |   1  |
|------x------x------|
|   4  |   3  |   2  |
|------|------|------|
relatif dir south(3):
|------|------|------|
|   4  |   5  |   6  |
|------x------x------|
|   3  |  xx  |   7  |
|------x------x------|
|   2  |   1  |   8  |
|------|------|------|
relatif dir west(4):
|------|------|------|
|   2  |   3  |   4  |
|------x------x------|
|   1  |  xx  |   5  |
|------x------x------|
|   8  |   7  |   6  |
|------|------|------|
*/
static const int step_add[WEST] = {
    1,
    3,
    5,
    -1
};

static int abs_to_relatif(enum direction_e dir, int abs)
{
    return abs + step_add[dir];
}

void send_broadcast_pos(ntw_client_t *trnt, int pos, const char *msg)
{
    char buff[512] = {0};
    client_t *cl;

    if (trnt == NULL || trnt->data == NULL) {
        return;
    }
    cl = trnt->data;
    if (pos != 0) {
        pos = abs_to_relatif(cl->cl.ai.trantorien->direction, pos);
    }
    snprintf(buff, 511, "message %d, ", pos);
    circular_buffer_write(trnt->write_to_outside, buff);
    circular_buffer_write(trnt->write_to_outside, msg);
    circular_buffer_write(trnt->write_to_outside, "\n");
}
