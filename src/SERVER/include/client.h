/*
** EPITECH PROJECT, 2023
** zappy server client
** File description:
** clients header
*/

#ifndef CLIENT_H_
    #define CLIENT_H_

    #include "trantorien.h"
    #include <stdbool.h>
    #define NAME_MAX 200

enum client_type_e {
    UNKNOWN = 0,
    GRAPHIC = 1,
    AI = 2,
};

enum client_connection_state_e {
    NOT_CONNECTED = 0,
    WAITING_TEAM_NAME = 1,
    CONNECTED = 2,
};

// TODO: modify this struct
struct client_graphic_s {
    int tmp;
};

// TODO: modify this struct
struct client_ai_s {
    trantorien_t *trantorien;
};

struct client_s {
    enum client_connection_state_e state;
    enum client_type_e type;
    char name[NAME_MAX];
    int id;
    union {
        struct client_graphic_s graphic;
        struct client_ai_s ai;
    } cl;
};
typedef struct client_s client_t;

/**
** @brief Initialize a new client
**
** @return the new client
**/
client_t *client_init(void);

/**
** @brief Destroy a client
**
** @param client the client
**/
void client_destroy(client_t *client);

#endif
