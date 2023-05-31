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

namespace GUI {
    namespace Components {
        class Sprite : public AComponent {
            public:
                Sprite(
                    const std::string &id,
                    sf::Texture &texture,
                    std::size_t layer,
                    const Vector2F &position = Vector2F(0, 0)
                );
                ~Sprite() = default;
                void setTexture(sf::Texture &texture);
                void setPosition(const sf::Vector2f &position);
                void setScale(const sf::Vector2f &scale);
                void setOrigin(const sf::Vector2f &origin);
                void setRotation(float rotation);
                std::size_t getLayer() const;
                void setLayer(std::size_t layer);
                const sf::Sprite &getSprite() const;

            private:
                sf::Sprite _sprite;
                std::size_t _layer;
                float _rotation;
                sf::Vector2f _position;
                sf::Vector2f _scale;
                sf::Vector2f _origin;
        };
    }
}
