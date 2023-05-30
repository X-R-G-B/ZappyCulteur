/*
** EPITECH PROJECT, 2021
** LIBMY
** File description:
** the file part of libmy
*/

#ifndef MY_FS_H_
    #define MY_FS_H_

/**
** @brief get the entire content of file path (if readable)
** @param path
** @return null if path is not readable; otherwise the content
**/
char *fs_get_content(char const *path);

/**
** @brief get size of the content of filepath (if stat can)
** @param path
** @return -1 if stat cant get size; the size else
**/
int fs_get_size(char const *path);

/**
** @brief open file path with read only
** @param path
** @return -1 if cant open; the file descriptor else
**/
int fs_open_ronly(char const *path);

#endif
