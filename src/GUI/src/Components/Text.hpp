/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** Sprite
*/

#pragma once

#include <SFML/Graphics.hpp>
#include "AComponent.hpp"
#include "Vector2F.hpp"
#include "Color.hpp"

namespace GUI {
    namespace Components {
        class Text : public AComponent {
            public:
                Text(
                    const std::string &id,
                    const std::string &text,
                    const Vector2F &position,
                    Color _color,
                    unsigned int size = 20,
                    CompType type = CompType::TEXT
                );
                ~Text() = default;
                void setPosition(const Vector2F &position);
                Vector2F getPosition() const;
                void setText(const std::string &text);
                const sf::Text &getText() const;
                void setColor(const Color &color);

            private:
                static constexpr const char *FONT_PATH = "src/GUI/assets/fonts/mainFont.ttf";
                sf::Text _text;
                sf::Font _font;
                Vector2F _position;
                Color _color;
        };
    }
}
