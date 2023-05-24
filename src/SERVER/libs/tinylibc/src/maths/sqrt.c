/*
** EPITECH PROJECT, 2022
** (my) Tiny Lib C
** File description:
** square root function
*/

#include "tlcmaths.h"

static const int accurency = 100;

static long double x_sqrtl_find(long double x, long double lower,
    long double higher, int accurency)
{
    long double mid = 0;
    long double tmp = 0;

    for (int i = 0; i < accurency; i++) {
        mid = (lower + higher) / 2;
        tmp = x_powl(mid, 2);
        if (tmp == x) {
            return (mid);
        }
        (tmp > x) ? (higher = mid) : (lower = mid);
    }
    return (mid);
}

static void x_sqrtl_bouds(long double *lower, long double *higher,
    long double (*power)(long double x, long double y), long double x)
{
    long double tmp_lo = 0;
    long double tmp_hi = 0;

    tmp_lo = power(*lower, 2);
    while (100 * tmp_lo < x) {
        *lower *= 10;
        tmp_lo *= 100;
    }
    tmp_hi = power(*higher, 2);
    while (0.01 * tmp_hi > x) {
        *higher *= 0.1;
        tmp_hi *= 0.01;
    }
}

double x_sqrt(double x)
{
    long double lower = x_mind(1, x);
    long double higher = x_maxd(1, x);
    double res = 0;

    if (x <= 1) {
        return (x);
    }
    x_sqrtl_bouds(&lower, &higher, x_powl, x);
    res = x_sqrtl_find(x, lower, higher, accurency);
    return (res);
}

float x_sqrtf(float x)
{
    long double lower = x_minf(1, x);
    long double higher = x_maxf(1, x);
    float res = 0;

    if (x <= 1) {
        return (x);
    }
    x_sqrtl_bouds(&lower, &higher, x_powl, x);
    res = x_sqrtl_find(x, lower, higher, accurency * 10);
    return (res);
}

long double x_sqrtl(long double x)
{
    long double lower = x_minl(1, x);
    long double higher = x_maxl(1, x);
    long double res = 0;

    if (x <= 1) {
        return (x);
    }
    x_sqrtl_bouds(&lower, &higher, x_powl, x);
    res = x_sqrtl_find(x, lower, higher, accurency * 100);
    return (res);
}
