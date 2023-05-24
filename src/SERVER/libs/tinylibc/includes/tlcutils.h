/*
** EPITECH PROJECT, 2022
** (my) Tiny Lib
** File description:
** utils function and macro
*/

#ifndef TLS_UTILS_H_
    #define TLS_UTILS_H_

    #define UNUSED __attribute__((unused))

/**
** @brief free if `ptr` is not null
**
** @param ptr to free
**/
void free_ifnotnull(void *ptr);

/**
** @brief function that do nothing; utils for ternary with one function call
**/
void return_void(void);

#endif
