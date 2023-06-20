/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** Text
*/

#include "Text.hpp"

namespace GUI {
    namespace Components {

        Text::Text(const std::string &id, const std::string &text,
        const Vector2F &position, Color color, unsigned int size, CompType type)
            : AComponent(id, type), _position(position), _color(color)
        {
            _font.loadFromFile(FONT_PATH);
            _text.setString(text);
            _text.setPosition(position.x, position.y);
            _text.setFillColor(sf::Color::White);
            _text.setFont(_font);
            _text.setCharacterSize(size);
        }

        void Text::setPosition(const Vector2F &position)
        {
            _position = position;
            _text.setPosition(position.x, position.y);
        }

        Vector2F Text::getPosition() const
        {
            return _position;
        }

        void Text::setText(const std::string &text)
        {
            _text.setString(text);
        }

        const sf::Text &Text::getText() const
        {
            return _text;
        }

        void Text::setColor(const Color &color)
        {
            _color = color;
            _text.setFillColor(sf::Color(color.getRed(), color.getGreen(),
            color.getBlue(), color.getAlpha()));
        }
    } // namespace Components
} // namespace GUI
