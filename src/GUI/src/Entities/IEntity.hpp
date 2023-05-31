/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** IEntity
*/

#pragma once

#include <string>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Vector2F.hpp"
#include "IComponent.hpp"

namespace GUI {
    namespace Entities {

        enum class EntityType {
            ENVIROMENT,
            RESOURCE,
            TRANTORIAN,
        };

        enum class EntityOrientation {
            UP,
            DOWN,
            LEFT,
            RIGHT,
        };

        class IEntity {
            public:
                virtual ~IEntity() = default;
                virtual void update() = 0;
                virtual const GUI::Vector2F &getPosition() const = 0;
                virtual void setPosition(const Vector2F &position) = 0;
                virtual const GUI::Vector2F &getRotation() const = 0;
                virtual void setRotation(const Vector2F &rotation) = 0;
                virtual const GUI::Vector2F &getScale() const = 0;
                virtual void setScale(const Vector2F &scale) = 0;
                virtual const EntityType &getType() const = 0;
                virtual const std::string &getId() const = 0;
                virtual void setOrientation(const EntityOrientation &orientation) = 0;
                virtual const EntityOrientation &getOrientation() const = 0;
                virtual const std::vector<Components::CompType> &getCompType() const = 0;
                virtual const std::vector<std::shared_ptr<Components::IComponent>> &getComponents() const = 0;
        };
    }
}
