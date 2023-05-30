/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** IEntity
*/

#pragma once

#include "Vector2F.hpp"

namespace GUI {
    namespace Entities {
        class IEntity {
            public:
                virtual ~IEntity() = default;
                virtual void update() = 0;
                virtual GUI::Vector2F getPosition() const = 0;
                virtual void setPosition(const Vector2F &position) = 0;
                virtual GUI::Vector2F getRotation() const = 0;
                virtual void setRotation(const Vector2F &rotation) = 0;
                virtual GUI::Vector2F getScale() const = 0;
                virtual void setScale(const Vector2F &scale) = 0;
        };
    }
}
