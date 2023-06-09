/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** update_food
*/

#include <unistd.h>
#include "circular_buffer.h"
#include "client.h"
#include "broadcast_events.h"
#include "llog.h"

static const char *format_str = "death of player AI id:%d";

static void send_event_death(ntw_t *ntw, int id, bool is_an_egg)
{
    if (is_an_egg) {
        cmd_edi(ntw, id);
    } else {
        cmd_pdi(ntw, id);
        llog_write_fd(STDERR_FILENO, LLOG_INFO, format_str, id);
    }
}

void update_food(ntw_t *ntw, trantorien_t *trantorien,
    ntw_client_t *cl, bool is_an_egg)
{
    if (trantorien == NULL || trantorien->alive == false) {
        return;
    }
    trantorien->food_stack_freq += 1;
    if (trantorien->food_stack_freq < MAX_FOOD_FREQ) {
        return;
    }
    trantorien->food_stack_freq = 0;
    if (trantorien->ressources[FOOD] > 0) {
        trantorien->ressources[FOOD]--;
    } else {
        trantorien->alive = false;
        if (cl) {
            circular_buffer_write(cl->write_to_outside, "dead\n");
        }
        send_event_death(ntw, trantorien->id, is_an_egg);
    }
}
