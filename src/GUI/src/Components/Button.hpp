/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** Button
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include "AComponent.hpp"
#include "Vector2F.hpp"
#include "EventsManager.hpp"

namespace GUI {
    namespace Components {
        class Button : public AComponent {

            enum class ButtonState {
                NONE,
                HOVERED,
                PRESSED
            };

            public:
                Button(
                    const std::string &id,
                    const std::string &text,
                    const Vector2F &position,
                    Event event
                );
                ~Button() = default;
                void setPosition(const Vector2F &position);
                Vector2F getPosition() const;
                void setText(const std::string &text);
                const sf::Text &getText() const;
                const sf::Sprite &getSprite() const;
                void update();

            private:
                void initSprites();
                void checkForFocus();
                sf::Text _text;
                sf::Font _font;
                Vector2F _position;
                std::string _btnText;
                Event _event;
                ButtonState _state;
                std::unordered_map<ButtonState, sf::Sprite> _sprites;
                std::unordered_map<ButtonState, sf::Texture> _textures;
        };
    }
}
