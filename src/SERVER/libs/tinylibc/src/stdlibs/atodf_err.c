/*
** EPITECH PROJECT, 2022
** libconv
** File description:
** get float from str
*/

#include <stddef.h>
#include "tlcstrings.h"

static int get_out_of_noise(char const *str, int *is_error)
{
    int i = 0;

    if (str == NULL) {
        *is_error = 1;
        return (84);
    }
    while (str[i] != '\0' && x_strcontainc("\b\t\n\v\f\r ", str[i])) {
        i++;
    }
    return (i);
}

static int check_if_negativ_number(char const *str, int i)
{
    int nb_minus = 0;

    while (str[i] != '\0' && x_strcontainc("+-", str[i])) {
        if (str[i] == '-') {
            nb_minus += 1;
        }
        i++;
    }
    return (nb_minus % 2 != 0);
}

static int get_out_of_sign(char const *str, int i, int *is_error)
{
    while (str[i] != '\0' && x_strcontainc("+-", str[i])) {
        i++;
    }
    if (x_strcontainc("123456789", str[i]) == 0) {
        *is_error = 1;
        return (84);
    }
    return (i);
}

static double get_absol_neg_result(char const *str, int i)
{
    int result = 0;
    int j = 0;
    double f_part = 0.0;

    while (str[i] != '\0' && x_strcontainc("0123456789", str[i])) {
        result *= 10;
        result -= str[i] - '0';
        i++;
    }
    if (str[i] == '\0' || str[i] != '.') {
        return (result * 1.0);
    }
    for (j = i + 1; str[j] != '\0' && x_strcontainc("0123456789", str[j]);
            j++);
    for (j = j - 1; str[j] != '.'; j--) {
        f_part *= 0.1;
        f_part -= (str[j] - '0') * 0.1;
    }
    return (result + f_part);
}

/**
** @brief get the float number in str
** @param str
** @param is_error
** @return 0 if there is an error and *is_error set to 1; the number else
**/
double x_atodf_err(char const *str, int *is_error)
{
    int i = 0;
    int nb_minus = 0;
    double result = 0;

    i = get_out_of_noise(str, is_error);
    if (*is_error) {
        return (0);
    }
    nb_minus = check_if_negativ_number(str, i);
    i = get_out_of_sign(str, i, is_error);
    if (*is_error) {
        return (0);
    }
    result = get_absol_neg_result(str, i);
    if (nb_minus == 0) {
        result *= -1;
    }
    return (result);
}
