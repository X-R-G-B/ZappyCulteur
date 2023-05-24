/*
** EPITECH PROJECT, 2022
** writer json
** File description:
** write json
*/

#include <fcntl.h>
#include <unistd.h>
#include "tlcjson.h"

const int modes = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;

int write_json(any_t *any, char const *path)
{
    int fd = 0;

    fd = open(path, O_WRONLY | O_TRUNC | O_CREAT, modes);
    if (fd <= 0) {
        return (JS_ERR_INPUT);
    }
    prety_print(any, fd);
    close(fd);
    return JS_OK;
}
