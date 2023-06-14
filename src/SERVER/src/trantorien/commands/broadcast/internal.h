/*
** EPITECH PROJECT, 2023
** zappy server trantorien command broadcast
** File description:
** internal header
*/

#ifndef INTERNAL_H_
    #define INTERNAL_H_

    #include <stdbool.h>
    #include "ntw.h"

    #define DIR_SIZE 8

bool is_in_box(float pos[2], float pos_sq[2], float size_sq[2]);
void send_broadcast_pos(ntw_client_t *trnt, int pos, const char *msg);

#endif
