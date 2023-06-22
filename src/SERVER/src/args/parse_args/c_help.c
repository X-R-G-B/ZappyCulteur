/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** c_help
*/

#include <stdbool.h>
#include <stdio.h>
#include "internal.h"

bool help_flag(__attribute__((unused)) const char *const arr[], args_t *args)
{
    puts("[HELP]\n"
        "This is the help of the zappy server\n"
        "USAGE: ./zappy_server -p port -x width -y height -n name1 name2 ... "
            "-c clientsNb -f freq\n"
        "\t-p (port)\tis the port number\n"
        "\t-x (width)\tis the width of the world\n"
        "\t-y (height)\tis the height of the world\n"
        "\t-n (name1 name2 ...)\tis the name of the team\n"
        "\t-c (clientsNb)\tis the number of authorized clients per team\n"
        "\t-f (freq)\tis the reciprocal of time unit for execution of "
            "actions\n");
    args->is_help = true;
    return true;
}
