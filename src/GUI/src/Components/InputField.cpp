/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** InputField
*/

#include <vector>
#include "InputField.hpp"
#include "EventsManager.hpp"

static const std::vector<GUI::Event> validKeys = {
    GUI::Event::KEYBOARD_A_PRESSED,
    GUI::Event::KEYBOARD_B_PRESSED,
    GUI::Event::KEYBOARD_C_PRESSED,
    GUI::Event::KEYBOARD_D_PRESSED,
    GUI::Event::KEYBOARD_E_PRESSED,
    GUI::Event::KEYBOARD_F_PRESSED,
    GUI::Event::KEYBOARD_G_PRESSED,
    GUI::Event::KEYBOARD_H_PRESSED,
    GUI::Event::KEYBOARD_I_PRESSED,
    GUI::Event::KEYBOARD_J_PRESSED,
    GUI::Event::KEYBOARD_K_PRESSED,
    GUI::Event::KEYBOARD_L_PRESSED,
    GUI::Event::KEYBOARD_M_PRESSED,
    GUI::Event::KEYBOARD_N_PRESSED,
    GUI::Event::KEYBOARD_O_PRESSED,
    GUI::Event::KEYBOARD_P_PRESSED,
    GUI::Event::KEYBOARD_Q_PRESSED,
    GUI::Event::KEYBOARD_R_PRESSED,
    GUI::Event::KEYBOARD_S_PRESSED,
    GUI::Event::KEYBOARD_T_PRESSED,
    GUI::Event::KEYBOARD_U_PRESSED,
    GUI::Event::KEYBOARD_V_PRESSED,
    GUI::Event::KEYBOARD_W_PRESSED,
    GUI::Event::KEYBOARD_X_PRESSED,
    GUI::Event::KEYBOARD_Y_PRESSED,
    GUI::Event::KEYBOARD_Z_PRESSED,
    GUI::Event::KEYBOARD_0_PRESSED,
    GUI::Event::KEYBOARD_1_PRESSED,
    GUI::Event::KEYBOARD_2_PRESSED,
    GUI::Event::KEYBOARD_3_PRESSED,
    GUI::Event::KEYBOARD_4_PRESSED,
    GUI::Event::KEYBOARD_5_PRESSED,
    GUI::Event::KEYBOARD_6_PRESSED,
    GUI::Event::KEYBOARD_7_PRESSED,
    GUI::Event::KEYBOARD_8_PRESSED,
    GUI::Event::KEYBOARD_9_PRESSED,
    GUI::Event::KEYBOARD_SPACE_PRESSED,
    GUI::Event::KEYBOARD_DOT_PRESSED
};

static const std::vector<GUI::Event> unfocusKeys = {
    GUI::Event::KEYBOARD_ENTER_PRESSED,
    GUI::Event::KEYBOARD_ESCAPE_PRESSED,
    GUI::Event::KEYBOARD_TAB_PRESSED,
    GUI::Event::KEYBOARD_UP_PRESSED,
    GUI::Event::KEYBOARD_DOWN_PRESSED,
    GUI::Event::KEYBOARD_LEFT_PRESSED,
    GUI::Event::KEYBOARD_RIGHT_PRESSED,
    GUI::Event::MOUSE_RIGHT_PRESSED
};

namespace GUI {
    namespace Components {

        InputField::InputField(
            const std::string &id,
            const std::string &placeholder,
            const Vector2F &position,
            unsigned int size
        ) :
            AComponent(id, CompType::INPUTFIELD),
            _position(position),
            _placeholder(placeholder),
            _isFocused(false)
        {
            _font.loadFromFile(FONT_PATH);
            _text.setString(placeholder);
            _text.setPosition(position.x, position.y);
            _text.setFillColor(
                sf::Color(
                    color.getRed(),
                    color.getGreen(),
                    color.getBlue(),
                    color.getAlpha()
                )
            );
            _text.setFont(_font);
            _text.setCharacterSize(size);
        }

        void InputField::setPosition(const Vector2F &position)
        {
            _position = position;
            _text.setPosition(position.x, position.y);
        }

        void InputField::update()
        {
            std::string temp = _text.getString();

            checkForFocus();
            if (_isFocused == true) {
                updateEvents();
            }
        }

        void InputField::updateEvents()
        {
            std::string temp = _text.getString();

            if (EventsManager::getInstance().isEventTriggered(Event::KEYBOARD_BACKSPACE_PRESSED) == true) {
                if (temp.size() > 0) {
                    temp.pop_back();
                }
            }
            for (const auto& key : validKeys) {
                if (EventsManager::getInstance().isEventTriggered(key) == true &&
                    temp.size() < MAX_CHARACTERS) {
                    temp += EventsManager::getInstance().getEventKey(key);
                }
            }
            for (const auto& key : unfocusKeys) {
                if (EventsManager::getInstance().isEventTriggered(key)) {
                    _isFocused = false;
                }
            }
            _text.setString(temp);
        }

        void InputField::checkForFocus()
        {
            if (EventsManager::getInstance().isEventTriggered(Event::MOUSE_LEFT_PRESSED) == true &&
                EventsManager::getInstance().getMousePos().x >= _position.x &&
                EventsManager::getInstance().getMousePos().x <= _position.x + _text.getLocalBounds().width &&
                EventsManager::getInstance().getMousePos().y >= _position.y &&
                EventsManager::getInstance().getMousePos().y <= _position.y + _text.getLocalBounds().height) {
                if (_text.getString() == _placeholder) {
                    _text.setString("");
                    _isFocused = true;
                }
            }
        }

        Vector2F InputField::getPosition() const
        {
            return _position;
        }

        void InputField::setText(const std::string &text)
        {
            _text.setString(text);
        }

        const sf::Text &InputField::getText() const
        {
            return _text;
        }
    }
}
