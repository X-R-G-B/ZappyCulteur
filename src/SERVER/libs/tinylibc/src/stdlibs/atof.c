/*
** EPITECH PROJECT, 2022
** libconv
** File description:
** change string to float (double)
*/

#include <stddef.h>
#include <unistd.h>
#include <stdlib.h>
#include "tlcstrings.h"
#include "tlcstdlibs.h"
#include "tlcmaths.h"

int get_float_gap(const char *str)
{
    int len = 0;
    int i = 0;

    for (; str[i] != '.' && str[i] != '\0'; i++);
    if (str[i] == '\0') {
        return 0;
    }
    i++;
    for (; str[i] != '\0'; i++, len++);
    return len;
}

int increment_str(char str, char *result, int *indx)
{
    if (str != '.') {
        result[*indx] = str;
        (*indx) += 1;
        result[*indx] = '\0';
    }
    return 0;
}

char *get_int_str(const char *str)
{
    char *result = NULL;
    int check = 0;
    int indx = 0;

    if (str == NULL) {
        return NULL;
    }
    for (; str[check] != '\0' && str[check] != '.'; check++);
    if (str[check] != '.') {
        return x_strdup(str);
    }
    result = malloc(sizeof(char) * x_strlen(str));
    for (int i = 0; str[i] != '\0'; i++) {
        increment_str(str[i], result, &indx);
    }
    return result;
}

double x_atof(const char *str)
{
    char *int_str = NULL;
    int gap_float = 0;
    int int_nbr = 0;
    double res = 0.0;

    if (str == NULL) {
        return 0;
    }
    int_str = get_int_str(str);
    int_nbr = x_atoi(int_str);
    gap_float = get_float_gap(str);
    res = ((double) int_nbr) / (x_pow(10, gap_float));
    free(int_str);
    return res;
}
