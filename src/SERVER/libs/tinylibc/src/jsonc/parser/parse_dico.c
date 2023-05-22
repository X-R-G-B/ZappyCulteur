/*
** EPITECH PROJECT, 2023
** (My) Tiny Lib C
** File description:
** parse dico json
*/
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "tlcjson.h"
#include "tlcdico.h"

bool is_tokken(const char *str, char tokken, int global_index, char escape);
any_t *parse_string(const char *str, int *global_index);
any_t *parse_unknow(const char *str, int *global_index);
bool parse_dico_is_empty(const char **str, int *global_index);

static any_t *get_key(const char **str, int *global_index)
{
    any_t *key = NULL;
    int tmp = 0;

    for (; **str != '\0' && is_tokken(*str, '"', *global_index, '\\') == false;
        (*str)++, (*global_index)++) {
    }
    tmp = *global_index;
    key = parse_string(*str, global_index);
    if (key == NULL) {
        return NULL;
    }
    *str = *str + (*global_index - tmp);
    for (; *(*str) != '\0' && is_tokken(*str, ':', *global_index, '\\')
        == false; (*str)++, (*global_index)++);
    return key;
}

static bool parse_dico_value(const char *str, int *global_index, dico_t *dico)
{
    any_t *key;
    any_t *value;
    bool err = false;

    key = get_key(&str, global_index);
    if (*str != ':') {
        destroy_any(key);
        return NULL;
    }
    str++;
    (*global_index)++;
    value = parse_unknow(str, global_index);
    if (value == NULL) {
        destroy_any(key);
        return false;
    }
    err = dico_add(dico, key->value.str, value, destroy_any) == NULL;
    destroy_any(key);
    return err == false;
}

static int to_next_case(const char **str, int *global_index, int temp)
{
    *str = *str + (*global_index - temp);
    for (; **str != '\0' &&
        is_tokken(*str, ',', *global_index, '\\') == false &&
        is_tokken(*str, '}', *global_index, '\\') == false;
        (*str)++, (*global_index)++);
    return *global_index;
}

static any_t *create_any_dico(dico_t *dico, int *global_index,
    const char *str)
{
    any_t *any = NULL;

    if (dico == NULL) {
        return NULL;
    }
    any = malloc(sizeof(any_t));
    if (any == NULL) {
        return NULL;
    }
    any->type = DICT;
    any->value.dict = dico;
    if (*str == '}') {
        (*global_index)++;
    }
    return any;
}

any_t *parse_dico(const char *str, int *global_index)
{
    dico_t *dico = NULL;

    if (str == NULL || *str == '\0' || *str != '{') {
        return NULL;
    }
    dico = dico_create();
    if (dico == NULL || parse_dico_is_empty(&str, global_index) == true) {
        return create_any_dico(dico, global_index, str);
    }
    for (int temp = *global_index; *str != '}' && *str != '\0';) {
        if (parse_dico_value(str, global_index, dico) == false) {
            dico_destroy(dico);
            return NULL;
        }
        temp = to_next_case(&str, global_index, temp);
    }
    return create_any_dico(dico, global_index, str);
}
