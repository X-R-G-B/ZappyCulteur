/*
** EPITECH PROJECT, 2022
** (my) TinyLibC
** File description:
** put a char
*/

#include <stdbool.h>
#include <unistd.h>
#include "tlcstdios.h"

int x_putc(char c, bool newline)
{
    return x_putcd(1, c, newline);
}

int x_putcd(int fd, char c, bool newline)
{
    int len = 0;
    char nl = '\n';

    len = write(fd, &c, 1);
    if (newline == true) {
        len += write(1, &nl, 1);
    }
    return (len);
}
