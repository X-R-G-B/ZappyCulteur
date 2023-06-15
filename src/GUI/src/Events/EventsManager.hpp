/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** Events
*/

#pragma once

#include <vector>
#include "Vector2F.hpp"

namespace GUI {
    enum class Event {
        //MOUSE EVENTS
        MOUSE_LEFT_PRESSED,
        MOUSE_RIGHT_PRESSED,
        //KEYBOARD NUMBERS
        KEYBOARD_1_PRESSED,
        KEYBOARD_2_PRESSED,
        KEYBOARD_3_PRESSED,
        KEYBOARD_4_PRESSED,
        KEYBOARD_5_PRESSED,
        KEYBOARD_6_PRESSED,
        KEYBOARD_7_PRESSED,
        KEYBOARD_8_PRESSED,
        KEYBOARD_9_PRESSED,
        KEYBOARD_0_PRESSED,
        //KEYBOARD LETTERS
        KEYBOARD_A_PRESSED,
        KEYBOARD_B_PRESSED,
        KEYBOARD_C_PRESSED,
        KEYBOARD_D_PRESSED,
        KEYBOARD_E_PRESSED,
        KEYBOARD_F_PRESSED,
        KEYBOARD_G_PRESSED,
        KEYBOARD_H_PRESSED,
        KEYBOARD_I_PRESSED,
        KEYBOARD_J_PRESSED,
        KEYBOARD_K_PRESSED,
        KEYBOARD_L_PRESSED,
        KEYBOARD_M_PRESSED,
        KEYBOARD_N_PRESSED,
        KEYBOARD_O_PRESSED,
        KEYBOARD_P_PRESSED,
        KEYBOARD_Q_PRESSED,
        KEYBOARD_R_PRESSED,
        KEYBOARD_S_PRESSED,
        KEYBOARD_T_PRESSED,
        KEYBOARD_U_PRESSED,
        KEYBOARD_V_PRESSED,
        KEYBOARD_W_PRESSED,
        KEYBOARD_X_PRESSED,
        KEYBOARD_Y_PRESSED,
        KEYBOARD_Z_PRESSED,
        //KEYBOARD ARROWS
        KEYBOARD_UP_PRESSED,
        KEYBOARD_DOWN_PRESSED,
        KEYBOARD_LEFT_PRESSED,
        KEYBOARD_RIGHT_PRESSED,
        //KEYBOARD SPECIALS
        KEYBOARD_SPACE_PRESSED,
        KEYBOARD_ENTER_PRESSED,
        KEYBOARD_BACKSPACE_PRESSED,
        KEYBOARD_TAB_PRESSED,
        KEYBOARD_ESCAPE_PRESSED,
        KEYBOARD_SHIFT_PRESSED,
        KEYBOARD_CTRL_PRESSED,
        KEYBOARD_ALT_PRESSED,
        //MOUSE WHEEL
        MOUSE_WHEEL_UP,
        MOUSE_WHEEL_DOWN,
        //WINDOW EVENTS
        WINDOW_CLOSED,
    };

    class EventsManager {
        public:
            
            /**
             * @brief Get the Events Manager object
             * 
             * @return EventsManager& 
             */
            static EventsManager &getInstance();

            /**
             * @brief Add an event to the events list
             * 
             * @param event 
             */
            void addEvent(Event event);

            /**
             * @brief Clear the current events list
             * 
             */
            void clearEvents();

            /**
             * @brief Return if the event is triggered
             * 
             * @param event 
             */
            bool isEventTriggered(Event event);

            /**
             * @brief Add the mouse position to the events manager
             * 
             * @param mousePos 
             */
            void addMousePos(Vector2F mousePos);

            /**
             * @brief Return the mouse position
             * 
             * @return Vector2F 
             */
            const Vector2F &getMousePos();

        private:
            EventsManager();
            ~EventsManager() = default;
            EventsManager(const EventsManager &) = delete;
            EventsManager &operator=(const EventsManager &) = delete;
            std::vector<Event> _eventsList;
            Vector2F _mousePos;
    };
}
