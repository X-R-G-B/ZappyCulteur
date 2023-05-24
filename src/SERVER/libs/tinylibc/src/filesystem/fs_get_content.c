/*
** EPITECH PROJECT, 2021
** LIBFILE
** File description:
** get filess content from a buffer
*/

#include <stdlib.h>
#include <unistd.h>
#include "tlcfs.h"
#include "tlcstrings.h"

static char *error_size(int size, int fd)
{
    char *str;

    close(fd);
    if (size < 0) {
        return (NULL);
    }
    str = malloc(sizeof(char));
    str[0] = '\0';
    return (str);
}

static char *error_malloc(int fd)
{
    close(fd);
    return (NULL);
}

static char *fill_buffer(int fd, char *buffer, int size)
{
    int nbyte = read(fd, buffer, size);

    if (nbyte != size) {
        free(buffer);
        close(fd);
        return (NULL);
    }
    buffer[size] = '\0';
    return (buffer);
}

/**
** @brief get the entire content of file path (if readable)
** @param path
** @return null if path is not readable; otherwise the content
**/
char *fs_get_content(char const *path)
{
    char *buffer = NULL;
    int size = 0;
    int fd = fs_open_ronly(path);

    if (fd < 0) {
        return (NULL);
    }
    size = fs_get_size(path);
    if (size <= 0) {
        return (error_size(size, fd));
    }
    buffer = malloc(sizeof(char) * (size + 1));
    if (buffer == NULL) {
        return (error_malloc(fd));
    }
    buffer = fill_buffer(fd, buffer, size);
    return (buffer);
}
