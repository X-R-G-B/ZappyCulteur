/*
** EPITECH PROJECT, 2022
** (my) Tiny Lib C
** File description:
** prototypes for math part
*/

#ifndef TLS_MATHS_H_
    #define TLS_MATHS_H_

    #define X_MAX_MACRO(x, y)   (((x) > (y)) ? (x) : (y))
    #define X_MIN_MACRO(x, y)   (((x) < (y)) ? (x) : (y))

    #define X_E                 2.7182818284
    #define X_PI                3.1415926535

/**
** @brief get max int between `a` and `b`
**
** @param a integer `a`
** @param b integer `b`
**
** @return `a` or `b`
**/
int x_max(int a, int b);

/**
** @brief get max double between `a` and `b`
**
** @param a double `a`
** @param b double `b`
**
** @return `a` or `b`
**/
double x_maxd(double a, double b);


/**
** @brief get max float between `a` and `b`
**
** @param a float `a`
** @param b float `b`
**
** @return `a` or `b`
**/
float x_maxf(float a, float b);

/**
** @brief get max long double between `a` and `b`
**
** @param a long double `a`
** @param b long double `b`
**
** @return `a` or `b`
**/
long double x_maxl(long double a, long double b);

/**
** @brief get min int between `a` and `b`
**
** @param a integer `a`
** @param b integer `b`
**
** @return `a` or `b`
**/
int x_min(int a, int b);

/**
** @brief get min double between `a` and `b`
**
** @param a double `a`
** @param b double `b`
**
** @return `a` or `b`
**/
double x_mind(double a, double b);


/**
** @brief get min float between `a` and `b`
**
** @param a float `a`
** @param b float `b`
**
** @return `a` or `b`
**/
float x_minf(float a, float b);

/**
** @brief get min long double between `a` and `b`
**
** @param a long double `a`
** @param b long double `b`
**
** @return `a` or `b`
**/
long double x_minl(long double a, long double b);

/**
** @brief `x` raise to the power of `y`
**
** @param x double
** @param y double
**
** @return `x` raise to the power of `y`
**/
double x_pow(double x, double y);

/**
** @brief `x` raise to the power of `y`
**
** @param x float
** @param y float
**
** @return `x` raise to the power of `y`
**/
float x_powf(float x, float y);

/**
** @brief `x` raise to the power of `y`
**
** @param x long double
** @param y long double
**
** @return `x` raise to the power of `y`
**/
long double x_powl(long double x, long double y);

/**
** @brief compute the square root of `x`
**
** @param x double
**
** @return x if (x <= 1);; square root of `x`
**/
double x_sqrt(double x);

/**
** @brief compute the square root of `x`
**
** @param x float
**
** @return x if (x <= 1);; square root of `x`
**/
float x_sqrtf(float x);

/**
** @brief compute the square root of `x`
**
** @param x long double
**
** @return x if (x <= 1);; square root of `x`
**/
long double x_sqrtl(long double x);

#endif
