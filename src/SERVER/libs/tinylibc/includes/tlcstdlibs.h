/*
** EPITECH PROJECT, 2022
** (my) Tiny Lib C
** File description:
** prototypes of stdlibs part
*/

#ifndef TLS_STDLIBS_H_
    #define TLS_STDLIBS_H_

/**
** @brief string (in base 10) to int
**
** @param x string to convert
**
** @return 0 if any error;; the number (could be 0 too)
**/
int x_atoi(const char *x);

/**
** @brief string (in custom base) to int
**
** len(`base`) must be > 1
**
** @param nb string to convert
** @param base base to use (ex for base 10: "0123456789")
**
** @return 0 if any error;; the number (could be 0 too)
**/
int atoi_base(const char *nb, const char *base);

/**
** @brief malloc n char and fill with 0
**
** @param n number to alloc
**
** @return ptr to the first n allocated
**/
char *x_calloc(int n);

/**
** @brief malloc n char * and fill with 0
**
** @param n number to alloc
**
** @return ptr to the first n allocated
**/
char **x_ccalloc(int n);

/**
** @brief int to string (malloc'd) in base 10 (0123456789)
**
** @param x number to convert
**
** @return NULL if any error;; the string
**/
char *x_itoa(int x);

/**
** @brief int to string (malloc'd) in base len(`base`) (`base`)
**
** len(`base`) must be > 1
**
** @param nb
** @param base
**
** @return NULL if any error;; the string
**/
char *itoa_base(int nb, char const *base);

/**
** @brief string (in base 10) to double
**
** @param str string to convert
**
** @return 0 if any error;; the number (could be 0 too)
**/
double x_atodf(char const *str);

/**
** @brief string (in base 10) to double
**
** @param str string to convert
** @param is_error if any error (is_error > 0 is an error)
**
** @return 0 if any error;; the number (could be 0 too)
**/
double x_atodf_err(char const *str, int *is_error);

/**
** @brief string (in base 10) to double
**
** @param str string to convert
**
** @return 0 if any error;; the number (could be 0 too)
**/
double x_atof(const char *str);

#endif
