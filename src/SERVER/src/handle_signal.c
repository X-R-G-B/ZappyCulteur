/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** handle_signal
*/

#include "handle_signal.h"

bool signal_end(bool end, bool set)
{
    static bool end_flag = false;

    if (set == true) {
        end_flag = end;
    }
    return end_flag;
}

void handle_signal(__attribute__((unused)) int sig)
{
    SET_SIGNAL_FLAG(true);
}
