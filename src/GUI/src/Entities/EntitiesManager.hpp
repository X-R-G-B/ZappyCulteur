/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** EntitiesManager
*/

#pragma once

#include <memory>
#include <stdexcept>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "IEntity.hpp"
#include "IComponent.hpp"

namespace GUI {
    namespace Entities {
        class EntitiesManager {
            
            class EntitiesManagerException : public std::exception {
                public:
                    explicit EntitiesManagerException(const std::string &message);
                    const char *what() const noexcept override;
                private:
                    std::string _message;
            };

            public:
                EntitiesManager() = default;
                ~EntitiesManager() = default;
                void update(double deltaTime);
                void killEntitiesByType(EntityType type);
                void killEntityById(const std::string &id);
                void addEntity(const std::shared_ptr<IEntity> &entity);
                const std::vector<std::shared_ptr<IEntity>> &getEntities() const;
                std::shared_ptr<IEntity> getEntityById(const std::string &id) const;
                std::unique_ptr<std::vector<std::shared_ptr<Components::IComponent>>>
                    getComponentsByType(Components::CompType type) const;
                std::unique_ptr<std::vector<std::shared_ptr<IEntity>>>
                    getEntitiesByType(EntityType type) const;
                bool doesEntityExist(const std::string &id) const;

            private:
                std::vector<std::shared_ptr<IEntity>> _entities;
        };
    }
}
