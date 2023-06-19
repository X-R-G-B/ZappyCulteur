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
                    const Vector2F &position = Vector2F(0, 0),
                    unsigned int width = 0,
                    unsigned int height = 0,
                    Components::CompType compType = Components::CompType::SPRITE
                );
                ~Sprite() = default;
                void setTexture(sf::Texture &texture);
                void setPosition(const sf::Vector2f &position);
                void setRect(const sf::IntRect &rect);
                sf::IntRect getRect() const;
                std::size_t getLayer() const;
                void setLayer(std::size_t layer);
                const sf::Sprite &getSprite() const;
                void applySize(unsigned int width, unsigned int height);

            private:
                sf::Sprite _sprite;
                std::size_t _layer;
                sf::Vector2f _position;
                sf::IntRect _rect;
        };
    }
}
