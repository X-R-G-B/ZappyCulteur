/*
** EPITECH PROJECT, 2022
** (my) Tiny Lib C
** File description:
** split str with delim
*/

#include <stddef.h>
#include <stdlib.h>
#include "tlcstrings.h"
#include "tlcstdlibs.h"

static int count_nb_split(const char *s, const char *delim)
{
    int nb_split = 0;
    const char *match = s;
    size_t len_delim = 0;

    do {
        nb_split += 1;
        s = match + len_delim;
        match = x_strstr(s, delim);
        len_delim = (len_delim == 0) ? x_strlen(delim) : len_delim;
    } while (match != NULL);
    return (nb_split);
}

static int fill_arr(char **arr, const char *s, const char *delim)
{
    size_t len_delim = 0;
    const char *match = s;
    int cur_arr = 0;

    do {
        s = match + len_delim;
        match = x_strstr(s, delim);
        if (match == NULL) {
            arr[cur_arr] = x_strdup(s);
        } else {
            arr[cur_arr] = x_strndup(s, match - s);
        }
        len_delim = (len_delim == 0) ? x_strlen(delim) : len_delim;
        cur_arr += 1;
    } while (match != NULL);
    return (0);
}

static int free_error(char **arr, int nb_split)
{
    if (arr == NULL) {
        return (0);
    }
    for (int i = 0; i < nb_split; i++) {
        if (arr[i] != NULL) {
            free(arr[i]);
        }
    }
    free(arr);
    return (0);
}

char **x_strsplit(const char *s, const char *delim)
{
    int nb_split = 0;
    char **arr = NULL;

    if (s == NULL || delim == NULL) {
        return (NULL);
    }
    nb_split = count_nb_split(s, delim);
    arr = x_ccalloc(sizeof(char **) * (nb_split + 1));
    if (arr == NULL) {
        return (NULL);
    }
    if (fill_arr(arr, s, delim) != 0) {
        free_error(arr, nb_split);
        return (NULL);
    }
    return (arr);
}
