/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** update_food
*/

#include "circular_buffer.h"
#include "client.h"

void update_food(trantorien_t *trantorien, ntw_client_t *cl, bool new_freq)
{
    if (!new_freq || trantorien == NULL || trantorien->alive == false) {
        return;
    }
    trantorien->food_stack_freq += new_freq;
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
    }
}
