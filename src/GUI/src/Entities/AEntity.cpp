/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** AEntity
*/

#include "AEntity.hpp"

namespace GUI {
    namespace Entities {
        GUI::Vector2F AEntity::getPosition() const
        {
            return _position;
        }

        void AEntity::setPosition(const Vector2F &position)
        {
            _position = position;
        }

        GUI::Vector2F AEntity::getRotation() const
        {
            return _rotation;
        }

        void AEntity::setRotation(const Vector2F &rotation)
        {
            _rotation = rotation;
        }

        GUI::Vector2F AEntity::getScale() const
        {
            return _scale;
        }

        void AEntity::setScale(const Vector2F &scale)
        {
            _scale = scale;
        }
    }
}
