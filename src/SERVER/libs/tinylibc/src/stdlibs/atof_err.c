/*
** EPITECH PROJECT, 2022
** libconv
** File description:
** get float from str
*/

#include <stddef.h>
#include "tlcstdlibs.h"
#include "tlcstrings.h"

static int get_int_len(int nb)
{
    int i = 0;

    if (nb < 0) {
        nb *= -1;
    }
    while (nb != 0) {
        nb /= 10;
        i++;
    }
    return (i);
}

static int get_after_decimal(char const *str)
{
    int i = 0;

    while (x_strcontainc("\b\t\n\v\f\r", str[i])) {
        i += 1;
    }
    while (x_strcontainc("+-", str[i])) {
        i += 1;
    }
    while (x_strcontainc("0123456789", str[i])) {
        i += 1;
    }
    return (i);
}

static int compute_power(int nb, int power)
{
    int result = 1;

    for (int i = 0; i < power; i++) {
        result *= nb;
    }
    return (result);
}

/*
** @brief get the float number in str
** @param str
** @param is_error
** @return 0 if there is an error and *is_error set to 1; the number else
**/
float x_atof_err(char const *str, int *is_error)
{
    int i = 0;
    int nb_part = 0;
    int float_part = 0;
    float result = 0.0;

    nb_part = x_atoi(str);
    if (*is_error) {
        return (0.0);
    }
    i = get_after_decimal(str);
    if (str[i] != '.') {
        return (nb_part);
    }
    float_part = x_atoi(str + i + 1);
    if (*is_error) {
        return (0.0);
    }
    result = ((float_part * 1.0) / compute_power(10, get_int_len(float_part)));
    return (nb_part + result);
}
