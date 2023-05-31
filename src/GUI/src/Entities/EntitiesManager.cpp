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

        const std::shared_ptr<IEntity> &EntitiesManager::getEntityById(const std::string &id) const
        {
            for (auto &entity : _entities) {
                if (entity->getId() == id) {
                    return entity;
                }
            }
            throw EntitiesManagerException("No entity with this id");
        }

        const std::vector<std::shared_ptr<IEntity>> &EntitiesManager::getEntitiesByType(EntityType type) const
        {
            std::vector<std::shared_ptr<IEntity>> entities;

            for (auto &entity : _entities) {
                if (entity->getType() == type) {
                    entities.push_back(entity);
                }
            }
            return entities;
        }

        const std::vector<std::shared_ptr<IEntity>> &EntitiesManager::getEntitiesByCompType(Components::CompType type) const
        {
            std::vector<std::shared_ptr<IEntity>> entities;

            for (auto &entity : _entities) {
                for (auto &compType : entity->getCompType()) {
                    if (compType == type) {
                        entities.push_back(entity);
                    }
                }
            }
            return entities;
        }

        void EntitiesManager::killEntityById(const std::string &id)
        {
            for (auto iterator = _entities.begin(); iterator != _entities.end(); iterator++) {
                if ((*iterator)->getId() == id) {
                    _entities.erase(iterator);
                    return;
                }
            }
            throw EntitiesManagerException("No entity with this id");
        }

        void EntitiesManager::killEntitiesByType(EntityType type)
        {
            for (auto iterator = _entities.begin(); iterator != _entities.end(); iterator++) {
                if ((*iterator)->getType() == type) {
                    _entities.erase(iterator);
                    return;
                }
            }
            throw EntitiesManagerException("No entity with this type");
        }
    }
}
