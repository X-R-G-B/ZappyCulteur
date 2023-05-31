/*
** EPITECH PROJECT, 2023
** zappy server loop
** File description:
** ai_cmd update
*/

#include <stdio.h>
#include <stdlib.h>
#include "circular_buffer.h"
#include "client.h"
#include "zappy.h"

<<<<<<< HEAD
bool update_ai_cmd(ntw_t *ntw, ntw_client_t *cl, args_t *args)
=======
bool update_ai_cmd(__attribute__((unused)) zappy_t *zappy, ntw_client_t *cl)
>>>>>>> dev
{
    char *tmp = NULL;

    tmp = circular_buffer_read(cl->read_from_outside);
    if (tmp == NULL) {
        return true;
    }
    fprintf(stderr, "%s%s\n", "ERROR: not implemented: ", tmp);
    free(tmp);
    circular_buffer_write(cl->write_to_outside, "ko\n");
    return true;
}
