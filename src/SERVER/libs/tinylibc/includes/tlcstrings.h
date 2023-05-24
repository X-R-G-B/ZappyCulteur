/*
** EPITECH PROJECT, 2022
** (my) Tiny Lib C
** File description:
** prototypes of strings part
*/

#ifndef TLS_STRINGS_H_
    #define TLS_STRINGS_H_

    #include <stddef.h>

/**
** @brief copy bytes of `src` to `dest`
**
** @param dest where bytes will go
** @param src the bytes source
** @param n number of bytes to copy
**
** @return NULL if (`dest` = 0)|(`src` = 0);; ptr `dest`
**/
void *x_memcpy(void *dest, const void *src, size_t n);

/**
** @brief search `c` in `s`
**
** @param s string in which to search for `c`
** @param c character to search in `s`
**
** @return NULL if `c` is not in `s`;; ptr to the character
**/
char *x_strchr(const char *s, int c);

/**
** @brief compare two strings
**
** @param s1 strings to compare to `s2`
** @param s2 strings to compare to `s1`
**
** @return 0 if `s1` = `s2`;; (s1[x] - s2[x]) where s1[x] and s2[x] are !=
**/
int x_strcmp(const char *s1, const char *s2);

/**
** @brief copy `src` in `dest` (`dest` must be able to store `src`)
**
** @param dest string where `src` will be copied
** @param src string of what to copy
**
** @return NULL if (`dest` = `src`)|(`dest` = 0)|(`src` = 0);; ptr to `dest`
**/
char *x_strcpy(char *dest, const char *src);

/**
** @brief duplicate a string
**
** @param s string to duplicate
**
** @return NULL if `s` = 0;; ptr to the new duplicate string
**/
char *x_strdup(const char *s);

/**
** @brief get length of a string
**
** @param s string to get the length
**
** @return 0 if `s` = 0;; the length
**/
size_t x_strlen(const char *s);

/**
** @brief copy `n` char of `src` in `dest`
**
** @param dest string where `n` char of `src` will go
** @param src string to copy
** @param n number of char to copy (if n > x_strlen(src), only x_strlen(src))
**
** @return NULL if (`dest` = 0)|(`src` = 0);; ptr to `dest`
**/
char *x_strncpy(char *dest, const char *src, size_t n);

/**
** @brief duplicate `n` char of a string
**
** @param s string to duplicate
** @param n number of char to duplicate
**
** @return NULL if (`s` = 0)|(`n` < 0);; ptr to the duplicate
**/
char *x_strndup(const char *s, int n);

/**
** @brief reverse a string
**
** @param str string to update
**
** @return NULL if (`str` = 0);; `str`
**/
char *x_strrev(char *str);

/**
** @brief split a string with delimiter
**
** @param s string to split
** @param delim string to use as a delimiter
**
** @return NULL if (`s` = 0)|(`delim` = 0);; array of string
**/
char **x_strsplit(const char *s, const char *delim);

/**
** @brief search a string in another string
**
** @param s string in which to search for `substr`
** @param substr string to search for in `s`
**
** @return NULL if (`s` = 0)|(`substr` = 0)(`substr` not found)|
** (`s` = "")|(`substr` = "");; ptr to match
**/
char *x_strstr(const char *s, const char *substr);

/**
** @brief remove character at start and end
**
** @param s string to strip the start and end of `chars` character
** @param chars character to strip
**
** @return NULL if (`s` = 0)|(`chars` = 0);; new string striped
**/
char *x_strstrip(const char *s, const char *chars);

/**
** @brief check if str contain c
** @param str
** @param c
** @return 1 if c is in str; 0 otherwise
**/
int x_strcontainc(char const *str, char const c);

/**
** @brief check if `str` ends with `needle`
**
** @param str
** @param needle
**
** @return 1 if `str` ends with `needle`; else 0
**/
int x_strendswith(const char *str, const char *needle);

#endif
