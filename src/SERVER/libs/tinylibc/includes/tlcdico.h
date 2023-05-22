/*
** EPITECH PROJECT, 2023
** (My) Tiny Lib C
** File description:
** dico header
*/

#ifndef TLS_DICO_H_
    #define TLS_DICO_H_

    #include <tlcllists.h>

struct dico_s {
    list_t *interns;
};
typedef struct dico_s dico_t;

struct dico_node_s {
    char key[256];
    void *value;
    void (*destroy)(void *value);
};
typedef struct dico_node_s dico_node_t;

/**
** @brief create a new dico
**
** @return dico
**/
dico_t *dico_create(void);

/**
** @brief delete a dico
**
** @param dico to delete
**/
void dico_destroy(dico_t *dico);

/**
** @brief add a key/value
**
** @param dico dico
** @param key key
** @param value value
** @param destroy destroy function to free the value (could be null)
**
** @return dico
**/
dico_t *dico_add(dico_t *dico, char const *key,
    void *value, void (*destroy)(void *value));

/**
** @brief add an elem (key/value/destroy)
**
** @param dico dico
** @param elem elem
**
** @return dico
**/
dico_t *dico_add_elem(dico_t *dico, dico_node_t *elem);

/**
** @brief remove a key and return the value
**
** @param dico dico
** @param key key
**
** @return value
**/
void *dico_pop_value(dico_t *dico, char const *key);

/**
** @brief remove a key and return the node
**
** @param dico dico
** @param key key
**
** @return node
**/
dico_node_t *dico_pop_elem(dico_t *elem, char const *key);

/**
** @brief Get value of pair key
**
** @param dico dico
** @param key key
**
** @return value
**/
void *dico_get_value(dico_t *dico, char const *key);

/**
** @brief Get node of pair key
**
** @param dico dico
** @param key key
**
** @return node
**/
dico_node_t *dico_get_elem(dico_t *dico, char const *key);

/**
** @brief Get node where value equal value in node
**
** @param dico dico
** @param value value
**
** @return node
**/
dico_node_t *dico_get_elem_ptr(dico_t *dico, void *value);

/**
** @brief Rem a key and its value
**
** @param dico dico
** @param key key
**
** @return dico
**/
dico_t *dico_rem(dico_t *dico, char const *key);

/**
** @brief Rem a key and its value
**
** @param dico dico
** @param value value of key/value pair
**
** @return dico
**/
dico_t *dico_rem_ptr(dico_t *dico, void *value);

#endif
