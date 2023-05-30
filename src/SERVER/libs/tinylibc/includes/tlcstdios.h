/*
** EPITECH PROJECT, 2022
** (my) TinyLibC
** File description:
** prototypes for stdios part
*/

#ifndef TLS_STDIOS_H_
    #define TLS_STDIOS_H_

    #include <stdbool.h>
    #include <stdarg.h>

/**
** @brief put `c` to stdout
**
** @param c character to put
** @param newline if put a newline after `c`
**
** @return number of character put
**/
int x_putc(char c, bool newline);

/**
** @brief put `str` to stdout (nothing if `str` = 0)
**
** @param str string to put
** @param newline if put a newline after `str`
**
** @return number of character put
**/
int x_puts(const char *str, bool newline);

/**
** @brief put a formated string to stdout (nothing if `format` = 0)
**
** in formated string: va arg: output
** %% : (nothing) : %
** %d : int       : (the number)
** %i : int       : (the number)
** %x : int       : (the number in hexa lower case)
** %X : int       : (the number in hexa upper case)
** %s : char *    : (the string)
** %c : char      : (the character)
** %p : void *    : (the ptr address in hexa lower case)
**
** @param format formated string
** @param ... (va arg)
**
** @return
**/
int x_printf(const char *format, ...);

/**
** @brief like printf but not output the string to stdout, put it in a string
**
** same format as x_printf()
**
** @param format (like x_printf())
** @param ... (like x_printf())
**
** @return NULL if `format` = 0;; the string formated
**/
char *x_sprintf(const char *format, ...);

/**
** @brief same as x_sprintf but take a va_list
**
** same format as x_printf()
**
** @param format (like x_printf())
** @param ap va_list from stdarg.h
**
** @return NULL if `format` = 0;; the string formated
**/
char *x_vsprintf(const char *format, va_list ap);

/**
** @brief Print to fd the str and put newline if bool true
**
** @param fd file descriptor
** @param str string
** @param newline need to put newline ?
**
** @return number of character put
**/
int x_putsd(int fd, const char *str, bool newline);

/**
** @brief Print to fd the c and put newline if bool true
**
** @param fd file descriptor
** @param c character
** @param newline put newline ?
**
** @return number of character put
**/
int x_putcd(int fd, char c, bool newline);

/**
** @brief Print to fd the str format and put newline if bool true
**
** @param fd file descriptor
** @param format format as printf
** @param ...
**
** @return number of character put
**/
int x_dprintf(int fd, const char *format, ...);

#endif
