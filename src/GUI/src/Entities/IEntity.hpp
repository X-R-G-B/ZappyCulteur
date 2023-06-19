/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** IEntity
*/

#pragma once

#include <string>
#include <exception>
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
            EGG,
            INCANTATION,
            HUD
        };

        enum class EntityOrientation {
            UP = 1,
            RIGHT,
            DOWN,
            LEFT,
        };

        bool operator<(Entities::EntityOrientation enitityO, int nbr);
        bool operator<(int nbr, Entities::EntityOrientation enitityO);
        bool operator>(Entities::EntityOrientation enitityO, int nbr);
        bool operator>(int nbr, Entities::EntityOrientation enitityO);

        class EntityException : public std::exception {
            public:
                EntityException(const std::string &message);
                const char *what() const noexcept override;
            private:
                std::string _message;
        };

        class IEntity {
            public:
                virtual ~IEntity() = default;
                virtual void update(double deltaTime) = 0;
                virtual const GUI::Vector2F &getPosition() const = 0;
                virtual void setPosition(const Vector2F &position) = 0;
                virtual const GUI::Vector2F &getRotation() const = 0;
                virtual void setRotation(const Vector2F &rotation) = 0;
                virtual const GUI::Vector2F &getScale() const = 0;
                virtual void setScale(const Vector2F &scale) = 0;
                virtual EntityType getType() const = 0;
                virtual const std::string &getId() const = 0;
                virtual void setOrientation(EntityOrientation orientation) = 0;
                virtual EntityOrientation getOrientation() const = 0;
                virtual const std::vector<Components::CompType> &getCompType() const = 0;
                virtual const std::vector<std::shared_ptr<Components::IComponent>>
                    &getComponents() const = 0;
                virtual std::unique_ptr<std::vector<std::shared_ptr<Components::IComponent>>>
                    getComponentsByType(Components::CompType type) const = 0;
        };
    }
}
