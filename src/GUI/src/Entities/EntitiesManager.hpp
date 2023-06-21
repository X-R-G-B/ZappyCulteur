/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** EntitiesManager
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>
#include "IComponent.hpp"
#include "IEntity.hpp"

namespace GUI {
    namespace Entities {

        class EntitiesManagerException : public std::exception {
            public:
                explicit EntitiesManagerException(const std::string &message);
                const char *what() const noexcept override;

            private:
                std::string _message;
        };

        class EntitiesManager {
            public:
                EntitiesManager() = default;
                ~EntitiesManager() = default;
                void update(double deltaTime);
                void killEntitiesByType(EntityType type);
                void killEntityById(const std::string &id);
                void killAllEntities();
                void addEntity(const std::shared_ptr<IEntity> &entity);
                const std::vector<std::shared_ptr<IEntity>> &
                getEntities() const;
                std::shared_ptr<IEntity> getEntityById(
                const std::string &id) const;
                std::unique_ptr<
                std::vector<std::shared_ptr<Components::IComponent>>>
                getComponentsByType(Components::CompType type) const;
                std::unique_ptr<std::vector<std::shared_ptr<IEntity>>>
                getEntitiesByType(EntityType type) const;
                bool doesEntityExist(const std::string &id) const;
                std::vector<std::string> getPlayersIds() const;

            private:
                std::vector<std::shared_ptr<IEntity>> _entities;
        };
    } // namespace Entities
} // namespace GUI
