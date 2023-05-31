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

        const EntityType &AEntity::getType() const
        {
            return _type;
        }

        const std::string &AEntity::getId() const
        {
            return _id;
        }

        void AEntity::setOrientation(const EntityOrientation &orientation)
        {
            _orientation = orientation;
        }

        const EntityOrientation &AEntity::getOrientation() const
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
