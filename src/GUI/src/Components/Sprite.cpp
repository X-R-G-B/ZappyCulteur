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
            const Vector2F &position
        ) :
            _sprite(texture),
            _layer(layer)
        {
            _id = id;
            _type = CompType::SPRITE;
            _rotation = 0;
            _position = sf::Vector2f(position.x, position.y);
            _scale = sf::Vector2f(1, 1);
            _origin = sf::Vector2f(0, 0);
            _sprite.setPosition(_position);
            _sprite.setScale(_scale);
            _sprite.setOrigin(_origin);
            _sprite.setRotation(_rotation);
        }
        
        void Sprite::setTexture(sf::Texture &texture)
        {
            _sprite.setTexture(texture);
        }
        
        void Sprite::setPosition(const sf::Vector2f &position)
        {
            _sprite.setPosition(position);
        }
        
        void Sprite::setScale(const sf::Vector2f &scale)
        {
            _sprite.setScale(scale);
        }
        
        void Sprite::setOrigin(const sf::Vector2f &origin)
        {
            _sprite.setOrigin(origin);
        }
        
        void Sprite::setRotation(float rotation)
        {
            _sprite.setRotation(rotation);
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
    }
}
