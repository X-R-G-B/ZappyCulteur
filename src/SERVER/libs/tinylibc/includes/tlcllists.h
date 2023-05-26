/*
** EPITECH PROJECT, 2022
** (my) Tiny Lib C
** File description:
** linked list part
*/

#ifndef TLS_LLISTS_H_
    #define TLS_LLISTS_H_

    #include <stdbool.h>
    #include "tlcutils.h"

typedef struct llnode node_t;
struct llnode {
    node_t *next;
    void *data;
    void (*destroy)(void *data);
    void *(*copy)(void *data);
};

typedef struct llist list_t;
struct llist {
    node_t *start;
    node_t *end;
    int len;
};

typedef struct llnodesearch node_result_t;
struct llnodesearch {
    node_t *node_ptr;
    int node_index;
};

    #define _COPY_CHECK(x) (x != 0 && (x)->copy != 0)
    #define _DESTROY_CHECK(x) (x != 0 && (x)->destroy != 0)
    #define _VOID(c, e) ((c) ? e : return_void())

    #define L_LEN(list) ((list != 0) ? (list)->len : 0)
    #define L_NEXT(node) ((node != 0) ? (node)->next : 0)
    #define L_FIRST(list) ((list != 0) ? (list)->start : 0)
    #define L_LAST(list) ((list != 0) ? (list)->end : 0)
    #define L_COPY(node) ((_COPY_CHECK(node)) ? \
        (node)->copy((node)->data) : 0)
    #define L_DATA(node) ((node != 0) ? (node)->data : 0)
    #define L_DATAT(type, node) ((type) L_DATA(node))
    #define L_GET(list, index) L_DATA(list_index(list, index))
    #define L_GETT(type, list, index) L_DATAT(type, list_index(list, index))
    #define L_DESTROY(x) (_VOID(_DESTROY_CHECK(x), (x)->destroy(L_DATA(x))))
    #define L_APPEND(list, value, destroy_ptr, copy_ptr) \
        list_append(list, value, destroy_ptr, copy_ptr)

    #define L_DECL_FIRST(x, list) node_t *x = L_FIRST(list)
    #define L_DECL_LAST(x, list) node_t *x = L_LAST(list)
    #define L_EACH(x, list) L_DECL_FIRST(x, list); x != 0; x = L_NEXT(x)

/**
** @brief append new data to `list`
**
** If `destroy` is NULL, the `data` will not be freed when the node is deleted
** If `copy` is NULL, the node will not be copied if you duplicate the list
**
** @param list the list to update
** @param data the data to append
** @param destroy the function called when need to destroy `data` (can be NULL)
** @param copy the function called when need to copy `data` (can be NULL)
**
** @return NULL if `list` = 0;; the `list`
**/
list_t *list_append(list_t *list, void *data, void (*destroy)(void *data),
    void *(*copy)(void *data));

/**
** @brief create an empty list
**
** @return NULL if malloc failed;; the new created list
**/
list_t *list_create(void);

/**
** @brief create a node
**
** If `destroy` is NULL, the `data` will not be freed when the node is deleted
** If `copy` is NULL, the node will not be copied if you duplicate the list
**
** @param data data to set
** @param destroy function to destroy `data` when needed (can be NULL)
** @param copy function to copy `data` when needed (can be NULL)
**
** @return NULL if malloc failed;; the new node created
**/
node_t *node_create(void *data, void (*destroy)(void *data),
    void *(*copy)(void *data));

/**
** @brief delete the `list`
**
** @param list list to delete
**/
void list_delete(list_t *list);

/**
** @brief duplicate `list`
**
** @param list the list to duplicate
**
** @return NULL if `list` = 0;; the new duplicated list
**/
list_t *list_duplicate(list_t *list);

/**
** @brief find node that have a node->data == `data`
**
** @param list the list in which to search
** @param data the ptr to search in `list`
**
** @return (node_index = -1 & node_ptr = 0) if not found;; the good info
**/
node_result_t list_find_ptrdata(list_t *list, void *data);

/**
** @brief find node index that have node == `node_ptr`
**
** @param list the list in which to search
** @param node_ptr the ptr to search in `list`
**
** @return -1 if not found;; the index
**/
int list_find_ptrnode(list_t *list, node_t *node_ptr);

/**
** @brief find node where is_this_result(node->data, `param`) = 1
**
** @param list the list in which to search
** @param is_this_result function that return 1 when the item is found
** @param param additional parameter to is_this_result
**
** @return (node_index = -1 & node_ptr = 0) if not found;; the good info
**/
node_result_t list_find_f(list_t *list,
    bool (is_this_result)(void *node_data, void *param), void *param);

/**
** @brief return node at index `index`
**
** If the index <= 0, it return the first node
** If the index is out of range, it return the last node
**
** @param list the list in which to search
** @param index the index of the node
**
** @return NULL if `list` = 0;; the node
**/
node_t *list_index(list_t *list, int index);

/**
** @brief insert `node` at end of `list`
**
** @param list list to update
** @param node node to add
**
** @return NULL if `list` = 0;; `list`
**/
list_t *list_insert_end(list_t *list, node_t *node);

/**
** @brief insert `node` at start of `list`
**
** @param list list to update
** @param node node to add
**
** @return NULL if `list` = 0;; `list`
**/
list_t *list_insert_start(list_t *list, node_t *node);

/**
** @brief insert `node` at index `index`
**
** If `node` = 0, the node will ne be added, and `list` will be returned
**
** @param list list to update
** @param node node to add
** @param index index where `node` will be in `list`
**
** @return NULL if `list` = 0;; `list`
**/
list_t *list_insert(list_t *list, node_t *node, int index);

/**
** @brief remove the first node of `list`
**
** @param list list to update
**
** @return 0 if (`list` = 0)|(`list`->len = 0);; 1
**/
int list_remove_start(list_t *list);

/**
** @brief remove the last node of `list`
**
** @param list list to update
**
** @return 0 if (`list` = 0)|(`list`->len = 0);; 1
**/
int list_remove_end(list_t *list);

/**
** @brief remove node where its ptr is `node`
**
** @param list list to update
** @param node ptr to the node to remove
**
** @return 0 if node not found;; 1
**/
int list_remove_ptrnode(list_t *list, node_t *node);

/**
** @brief remove node where node data is `ptdrdata`
**
** @param list list to update
** @param ptrdata ptr of data where data is in the node to remove
**
** @return 0 if node not found;; 1
**/
int list_remove_ptrdata(list_t *list, void *ptrdata);

#endif
