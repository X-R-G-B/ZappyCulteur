/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** InputField
*/

#pragma once

#include <SFML/Graphics.hpp>
#include "AComponent.hpp"
#include "Vector2F.hpp"
#include "Color.hpp"

namespace GUI {
    namespace Components {
        class InputField : public AComponent {
            public:
                InputField(
                    const std::string &id,
                    const std::string &placeholder,
                    const Vector2F &position,
                    unsigned int size = 20
                );
                ~InputField() = default;
                void setPosition(const Vector2F &position);
                Vector2F getPosition() const;
                void setText(const std::string &text);
                const sf::Text &getText() const;
                void update();

            private:
                void checkForFocus();
                void updateEvents();
                static constexpr char *FONT_PATH = "src/GUI/assets/fonts/mainFont.ttf";
                static constexpr std::size_t MAX_CHARACTERS = 20;
                sf::Text _text;
                sf::Font _font;
                Vector2F _position;
                Color _color;
                std::string _placeholder;
                bool _isFocused;
        };
    }
}
