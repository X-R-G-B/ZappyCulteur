/*
** EPITECH PROJECT, 2023
** zappy server trantorien command broadcast
** File description:
** helper is in box
*/

#include <stdbool.h>
#include <math.h>

bool is_in_box(float pos[2], float pos_sq[2], float size_sq[2])
{
    float x_min_sq = fmin(pos_sq[0], pos_sq[0] + size_sq[0]);
    float y_min_sq = fmin(pos_sq[1], pos_sq[1] + size_sq[1]);
    float x_max_sq = fmax(pos_sq[0], pos_sq[0] + size_sq[0]);
    float y_max_sq = fmax(pos_sq[1], pos_sq[1] + size_sq[1]);
    float x = pos[0];
    float y = pos[1];

    if (x_min_sq < x && x < x_max_sq &&
            y_min_sq < y && y < y_max_sq) {
        return true;
    }
    return false;
}
