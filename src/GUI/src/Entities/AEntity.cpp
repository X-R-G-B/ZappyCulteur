/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** AEntity
*/

#include "AEntity.hpp"
#include <iostream>

namespace GUI {
    namespace Entities {

        bool operator<(Entities::EntityOrientation enitityO, int nbr)
        {
            return static_cast<int>(enitityO) < nbr;
        }

        bool operator<(int nbr, Entities::EntityOrientation enitityO)
        {
            return nbr < static_cast<int>(enitityO);
        }

        bool operator>(Entities::EntityOrientation enitityO, int nbr)
        {
            return static_cast<int>(enitityO) > nbr;
        }

        bool operator>(int nbr, Entities::EntityOrientation enitityO)
        {
            return nbr > static_cast<int>(enitityO);
        }

        EntityException::EntityException(const std::string &message) :
            _message(message)
        {}

        const char *EntityException::what() const noexcept
        {
            return _message.c_str();
        }

        AEntity::AEntity(
            const std::string &id,
            const Vector2F &position,
            const Vector2F &rotation,
            const Vector2F &scale,
            EntityType type,
            EntityOrientation orientation
        ) :
            _position(position),
            _rotation(rotation),
            _scale(scale),
            _type(type),
            _id(id),
            _orientation(orientation)
        {}

        const GUI::Vector2F &AEntity::getPosition() const
        {
            return _position;
        }

        void AEntity::setPosition(const Vector2F &position)
        {
            _position = position;
        }

        const GUI::Vector2F &AEntity::getRotation() const
        {
            return _rotation;
        }

        void AEntity::setRotation(const Vector2F &rotation)
        {
            _rotation = rotation;
        }

        const GUI::Vector2F &AEntity::getScale() const
        {
            return _scale;
        }

        void AEntity::setScale(const Vector2F &scale)
        {
            _scale = scale;
        }

        EntityType AEntity::getType() const
        {
            return _type;
        }

        const std::string &AEntity::getId() const
        {
            return _id;
        }

        void AEntity::setOrientation(EntityOrientation orientation)
        {
            _orientation = orientation;
        }

        EntityOrientation AEntity::getOrientation() const
        {
            return _orientation;
        }

        const std::vector<Components::CompType> &AEntity::getCompType() const
        {
            return _entityCompType;
        }

        const std::vector<std::shared_ptr<Components::IComponent>> &AEntity::getComponents() const
        {
            return _components;
        }

        std::unique_ptr<std::vector<std::shared_ptr<Components::IComponent>>> 
            AEntity::getComponentsByType(Components::CompType type) const
        {
            std::unique_ptr<std::vector<std::shared_ptr<Components::IComponent>> > components =
                std::make_unique<std::vector<std::shared_ptr<Components::IComponent>> >();

            for (auto &component : _components) {
                if (component->getType() == type) {
                    components->push_back(component);
                }
            }
            return components;
        }
    }
}
