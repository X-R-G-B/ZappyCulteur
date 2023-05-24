/*
** EPITECH PROJECT, 2022
** libjson
** File description:
** parse
*/

#include <stdbool.h>
#include <stdlib.h>
#include "tlcdico.h"
#include "tlcllists.h"
#include "tlcstrings.h"
#include "tlcjson.h"
#include "tlcfs.h"

any_t *parse_unknow(const char *str, int *global_index);

any_t *parse_json_file(char const path[])
{
    char *str = NULL;
    any_t *retany = NULL;

    if (path == NULL) {
        return NULL;
    }
    str = fs_get_content(path);
    if (str == NULL) {
        return NULL;
    }
    retany = parse_json_str(str);
    free(str);
    return retany;
}

bool is_tokken(const char *str, char tokken, int global_index, char escape)
{
    if (global_index < 0 || str == NULL || *str == '\0' || *str != tokken) {
        return false;
    }
    if (global_index == 0 || *(str - 1) != escape ||
            (global_index > 1 && *(str - 2) == escape)) {
        return true;
    }
    return false;
}

any_t *parse_json_str(char const *str)
{
    any_t *ret_any = NULL;
    int global_index = 0;

    if (str == NULL) {
        return NULL;
    }
    ret_any = parse_unknow(str, &global_index);
    return ret_any;
}
