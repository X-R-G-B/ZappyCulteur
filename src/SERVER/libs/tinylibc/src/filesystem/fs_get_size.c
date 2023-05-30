/*
** EPITECH PROJECT, 2021
** LIBFILE
** File description:
** return the nbyte of a file
*/

#include <unistd.h>
#include "tlcfs.h"

/**
** @brief get size of the content of filepath (if stat can)
** @param path
** @return -1 if stat cant get size; the size else
**/
int fs_get_size(char const *path)
{
    int fd = 0;
    int ret = 0;
    int buf_ret = 0;
    char buffer[512];

    fd = fs_open_ronly(path);
    if (fd <= 0) {
        return (-1);
    }
    buf_ret = read(fd, buffer, 512);
    while (buf_ret > 0) {
        ret += buf_ret;
        buf_ret = read(fd, buffer, 512);
    }
    ret += buf_ret;
    return (ret);
}
