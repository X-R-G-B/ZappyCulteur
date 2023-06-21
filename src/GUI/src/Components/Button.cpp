/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** Button
*/

#include <vector>
#include "Button.hpp"
#include "EventsManager.hpp"

static const std::string BTN_UI_PATH = "src/GUI/assets/UI/button.png";
static const std::string BTN_UI_PATH_HOVERED = "src/GUI/assets/UI/buttonHover.png";
static const std::string BTN_UI_PATH_PRESSED = "src/GUI/assets/UI/buttonClicked.png";
static const GUI::Vector2F BTN_TEXT_OFFSET = {40, 15};
static constexpr unsigned int BTN_FONT_SIZE = 30;
static const float BTN_SIZE_X = 451;
static const float BTN_SIZE_Y = 86;
static const std::string PATH_FONT = "src/GUI/assets/fonts/mainFont.ttf";

namespace GUI {
    namespace Components {

        Button::Button(
            const std::string &id,
            const std::string &text,
            const Vector2F &position,
            Event event
        ) : AComponent(id, CompType::BUTTON), _position(position), _btnText(text), _event(event),
            _state(ButtonState::NONE)
        {
            initSprites();
            _state = ButtonState::NONE;
            _font.loadFromFile(PATH_FONT);
            _text.setFont(_font);
            _text.setString(text);
            _text.setCharacterSize(BTN_FONT_SIZE);
            _text.setFillColor(sf::Color::White);
            _text.setPosition(_position.x + BTN_TEXT_OFFSET.x, _position.y + BTN_TEXT_OFFSET.y);
        }
  
        void Button::initSprites()
        {
            _textures[ButtonState::NONE].loadFromFile(BTN_UI_PATH);
            _textures[ButtonState::HOVERED].loadFromFile(BTN_UI_PATH_HOVERED);
            _textures[ButtonState::PRESSED].loadFromFile(BTN_UI_PATH_PRESSED);
            _sprites[ButtonState::NONE].setTexture(_textures[ButtonState::NONE]);
            _sprites[ButtonState::HOVERED].setTexture(_textures[ButtonState::HOVERED]);
            _sprites[ButtonState::PRESSED].setTexture(_textures[ButtonState::PRESSED]);
            _sprites[ButtonState::NONE].setPosition(_position.x, _position.y);
            _sprites[ButtonState::HOVERED].setPosition(_position.x, _position.y);
            _sprites[ButtonState::PRESSED].setPosition(_position.x, _position.y);
        }

        void Button::checkForFocus()
        {
            _state = ButtonState::NONE;
            EventsManager &eventsManager = EventsManager::getInstance();

            if (EventsManager::getInstance().getMousePos().x >= _position.x &&
                EventsManager::getInstance().getMousePos().x <= _position.x + BTN_SIZE_X &&
                EventsManager::getInstance().getMousePos().y >= _position.y &&
                EventsManager::getInstance().getMousePos().y <= _position.y + BTN_SIZE_Y) {
                if (EventsManager::getInstance().isEventTriggered(Event::MOUSE_LEFT_PRESSED) == true) {
                    _state = ButtonState::PRESSED;
                    eventsManager.addEvent(_event);
                } else {
                    _state = ButtonState::HOVERED;
                }
            }
        }

        void Button::setPosition(const Vector2F &position)
        {
            _position = position;
            _sprites[ButtonState::NONE].setPosition(_position.x, _position.y);
            _sprites[ButtonState::HOVERED].setPosition(_position.x, _position.y);
            _sprites[ButtonState::PRESSED].setPosition(_position.x, _position.y);
        }

        Vector2F Button::getPosition() const
        {
            return _position;
        }

        void Button::setText(const std::string &text)
        {
            _btnText = text;
            _text.setString(text);
        }

        const sf::Text &Button::getText() const
        {
            return _text;
        }

        const sf::Sprite &Button::getSprite() const
        {
            return _sprites.at(_state);
        }

        void Button::update()
        {
            checkForFocus();
        }
    }
}
