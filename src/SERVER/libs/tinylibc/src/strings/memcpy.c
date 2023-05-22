/*
** EPITECH PROJECT, 2022
** (my) Tiny Lib C
** File description:
** copy memory
*/

#include <stddef.h>

void *x_memcpy(void *dest, const void *src, size_t n)
{
    const unsigned char *src_c = NULL;
    unsigned char *dest_c = NULL;

    if (dest == NULL || src == NULL) {
        return (NULL);
    }
    src_c = src;
    dest_c = dest;
    for (size_t i = 0; i < n; i++) {
        dest_c[i] = src_c[i];
    }
    return dest;
}
