/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** handle_signal
*/

#ifndef HANDLE_SIGNAL_H_
    #define HANDLE_SIGNAL_H_

    #include <signal.h>
    #include <stdbool.h>

    #define SIGNAL_FLAG signal_end(0, false)
    #define SET_SIGNAL_FLAG(b) signal_end(b, true)

bool signal_end(bool end, bool set);
void handle_signal(int sig);

#endif // HANDLE_SIGNAL_H
