/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** AEntity
*/

#pragma once

#include "IEntity.hpp"

namespace GUI {
    namespace Entities {
        class AEntity : public IEntity {
            public:
                ~AEntity() = default;
                GUI::Vector2F getPosition() const override;
                void setPosition(const Vector2F &position) override;
                GUI::Vector2F getRotation() const override;
                void setRotation(const Vector2F &rotation) override;
                GUI::Vector2F getScale() const override;
                void setScale(const Vector2F &scale) override;
                EntityType getType() const override;
            protected:
                Vector2F _position;
                Vector2F _rotation;
                Vector2F _scale;
                EntityType _type;
        };
    }
}
