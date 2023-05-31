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
                const GUI::Vector2F &getPosition() const final;
                void setPosition(const Vector2F &position) final;
                const GUI::Vector2F &getRotation() const final;
                void setRotation(const Vector2F &rotation) final;
                const GUI::Vector2F &getScale() const final;
                void setScale(const Vector2F &scale) final;
                const EntityType &getType() const final;
                const std::string &getId() const final;
                void setOrientation(const EntityOrientation &orientation) final;
                const EntityOrientation &getOrientation() const final;
                const std::vector<Components::CompType> &getCompType() const final;
                const std::vector<std::shared_ptr<Components::IComponent>>
                    &getComponents() const final;
                std::unique_ptr<std::vector<std::shared_ptr<Components::IComponent>>>
                    getComponentsByType(Components::CompType type) const final;
            protected:
                Vector2F _position;
                Vector2F _rotation;
                Vector2F _scale;
                EntityType _type;
                std::string _id;
                EntityOrientation _orientation;
                std::vector<Components::CompType> _entityCompType;
                std::vector<std::shared_ptr<Components::IComponent>> _components;
        };
    }
}
