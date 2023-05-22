/*
** EPITECH PROJECT, 2021
** LIBFILE
** File description:
** open a file in read only
*/

#include <fcntl.h>

/**
** @brief open file path with read only
** @param path
** @return -1 if cant open; the file descriptor else
**/
int fs_open_ronly(char const *path)
{
    return (open(path, O_RDONLY));
}
