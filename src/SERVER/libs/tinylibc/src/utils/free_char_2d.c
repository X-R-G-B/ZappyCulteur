/*
** EPITECH PROJECT, 2023
** tinylibc
** File description:
** free 2d array of string (null terminated)
*/

#include <stdlib.h>
#include "tlcutils.h"

void free_char_2d(char **arr)
{
    if (arr == NULL) {
        return;
    }
    for (int i = 0; arr[i] != NULL; i++) {
        if (arr[i] != NULL) {
            free(arr[i]);
        }
    }
    free(arr);
}
