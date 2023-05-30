/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** EntitiesManager
*/

#include "EntitiesManager.hpp"

namespace GUI {
    namespace Entities {

        EntitiesManager::EntitiesManagerException::EntitiesManagerException(const std::string &message) :
            _message(message) {}

        const char *EntitiesManager::EntitiesManagerException::what() const noexcept
        {
            return _message.c_str();
        }

        void EntitiesManager::update()
        {
            for (auto &entity : _entities) {
                //update the rect, the pos if needed, etc...
                entity->update();
            }
        }

        void EntitiesManager::addEntity(const std::shared_ptr<IEntity> &entity)
        {
            _entities.push_back(entity);
        }

        const std::vector<std::shared_ptr<IEntity>> &EntitiesManager::getEntities() const
        {
            return _entities;
        }

        const std::shared_ptr<IEntity> &EntitiesManager::getEntityById(
            EntityType type, const std::string &id) const
        {
            for (auto &entity : _entities) {
                if (entity->getType() == type && entity->getId() == id) {
                    return entity;
                }
            }
            throw EntitiesManagerException("No entity found with this id");
        }

        void EntitiesManager::killEntitiesByType(EntityType type)
        {
            for (auto &entity : _entities) {
                if (entity->getType() == type) {
                    entity.reset();
                }
            }
        }

        void EntitiesManager::killEntityById(EntityType type, const std::string &id)
        {
            for (auto &entity : _entities) {
                if (entity->getType() == type && entity->getId() == id) {
                    entity.reset();
                    return;
                }
            }
        }

        std::unique_ptr<std::vector<std::shared_ptr<IEntity>>>
            EntitiesManager::getEntitiesByType(EntityType type) const
        {
            auto entities = std::make_unique<std::vector<std::shared_ptr<IEntity>>>();

            for (auto &entity : _entities) {
                if (entity->getType() == type) {
                    entities->push_back(entity);
                }
            }
            return entities;
        }
    }
}
