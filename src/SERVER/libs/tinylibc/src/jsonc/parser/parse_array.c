/*
** EPITECH PROJECT, 2023
** (My) Tiny Lib C
** File description:
** parse array json
*/

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "tlcjson.h"
#include "tlcllists.h"

any_t *parse_unknow(const char *str, int *global_index);
bool is_tokken(const char *str, char tokken, int global_index, char escape);
bool parse_array_is_empty(const char **str, int *global_index);

static bool parse_array_index(const char *str, int *global_index,
    list_t *list)
{
    any_t *any = NULL;

    if (list == NULL) {
        return false;
    }
    any = parse_unknow(str, global_index);
    if (any == NULL) {
        return false;
    }
    if (list_append(list, any, destroy_any, NULL)) {
        return true;
    }
    return false;
}

static int to_next_case(const char **str, int *global_index, int temp)
{
    *str = *str + (*global_index - temp);
    for (; **str != '\0' &&
        is_tokken(*str, ',', *global_index, '\\') == false &&
        is_tokken(*str, ']', *global_index, '\\') == false;
        (*str)++, (*global_index)++);
    return *global_index;
}

static any_t *create_any_array(list_t *list, int *global_index,
    const char *str)
{
    any_t *any = NULL;

    if (list == NULL) {
        return NULL;
    }
    any = malloc(sizeof(any_t));
    if (any == NULL) {
        return NULL;
    }
    any->type = ARRAY;
    any->value.array = list;
    if (*str == ']') {
        (*global_index)++;
    }
    return any;
}

static any_t *parse_array_loop(const char *str, int *global_index,
    list_t *list)
{
    if (*str == '[') {
        str++;
        (*global_index)++;
    }
    for (int temp = *global_index; *str != '\0' && *str != ']';) {
        if (parse_array_index(str, global_index, list) == false) {
            list_delete(list);
            return NULL;
        }
        temp = to_next_case(&str, global_index, temp);
    }
    return create_any_array(list, global_index, str);
}

any_t *parse_array(const char *str, int *global_index)
{
    list_t *list = NULL;

    if (str == NULL || *str == '\0' || *str != '[') {
        return NULL;
    }
    list = list_create();
    if (list == NULL) {
        return NULL;
    }
    if (parse_array_is_empty(&str, global_index) == true) {
        return create_any_array(list, global_index, str);
    }
    return parse_array_loop(str, global_index, list);
}
