/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** update_food
*/

#include "circular_buffer.h"
#include "client.h"
#include "broadcast_events.h"

static void send_event_death(ntw_t *ntw, ntw_client_t *cl, bool is_an_egg)
{
    if (is_an_egg) {
        cmd_edi(ntw, cl);
    }
    cmd_pdi(ntw, cl);
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
            send_event_death(ntw, cl, is_an_egg);
        }
    }
}
