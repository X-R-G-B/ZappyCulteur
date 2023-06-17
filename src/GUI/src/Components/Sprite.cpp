/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** Sprite
*/

#include "Sprite.hpp"

namespace GUI {
    namespace Components {
        Sprite::Sprite(
            const std::string &id,
            sf::Texture &texture,
            std::size_t layer,
            const Vector2F &position,
            unsigned int width,
            unsigned int height,
            Components::CompType compType
        ) : AComponent(id, compType),
            _sprite(texture),
            _layer(layer)
        {
            _position = sf::Vector2f(position.x, position.y);
            _sprite.setPosition(_position);
            applySize(width, height);
        }

        void Sprite::setTexture(sf::Texture &texture)
        {
            _sprite.setTexture(texture);
        }

        void Sprite::setRect(const sf::IntRect &rect)
        {
            _sprite.setTextureRect(rect);
        }

        sf::IntRect Sprite::getRect() const
        {
            return _sprite.getTextureRect();
        }

        void Sprite::setPosition(const sf::Vector2f &position)
        {
            _sprite.setPosition(position);
        }

        std::size_t Sprite::getLayer() const
        {
            return _layer;
        }

        void Sprite::setLayer(std::size_t layer)
        {
            _layer = layer;
        }

        const sf::Sprite &Sprite::getSprite() const
        {
            return _sprite;
        }

        void Sprite::applySize(unsigned int width, unsigned int height)
        {
            if (width != 0 && height != 0) {
                _sprite.setScale(
                    sf::Vector2f(
                        static_cast<float>(width) / _sprite.getTexture()->getSize().x,
                        static_cast<float>(height) / _sprite.getTexture()->getSize().y
                    )
                );
            }
        }
    }
}
