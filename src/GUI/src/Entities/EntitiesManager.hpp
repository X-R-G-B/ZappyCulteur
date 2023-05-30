/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** EntitiesManager
*/

#pragma once

#include <memory>
#include <stdexcept>
#include <vector>
#include <string>
#include "IEntity.hpp"

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
                void update();
                void addEntity(const std::shared_ptr<IEntity> &entity);
                const std::vector<std::shared_ptr<IEntity>> &getEntities() const;
                const std::shared_ptr<IEntity> &getEntityById(EntityType type, const std::string &id) const;
                void killEntitiesByType(EntityType type);
                void killEntityById(EntityType type, const std::string &id);
                std::unique_ptr<std::vector<std::shared_ptr<IEntity>>> getEntitiesByType(EntityType type) const;
            private:
                std::vector<std::shared_ptr<IEntity>> _entities;
        };
    }
}
