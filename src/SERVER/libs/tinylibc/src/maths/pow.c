/*
** EPITECH PROJECT, 2022
** (my) Tiny Lib C
** File description:
** power function
*/

double x_pow(double x, double y)
{
    double res = 1;

    if (x == 1 || y == 1) {
        return (1);
    }
    for (int i = 0; i < y; i++) {
        res *= x;
    }
    return (res);
}

float x_powf(float x, float y)
{
    float res = 1;

    if (x == 1 || y == 1) {
        return (1);
    }
    for (int i = 0; i < y; i++) {
        res *= x;
    }
    return (res);
}

long double x_powl(long double x, long double y)
{
    long double res = 1;

    if (x == 1 || y == 1) {
        return (1);
    }
    for (int i = 0; i < y; i++) {
        res *= x;
    }
    return (res);
}
