/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** EntitiesManager
*/

#include "EntitiesManager.hpp"
#include "Trantorian.hpp"
#include "Expulsion.hpp"
#include "InputField.hpp"
#include "Button.hpp"

namespace GUI {
    namespace Entities {

        EntitiesManagerException::EntitiesManagerException(
        const std::string &message)
            : _message(message)
        {
        }

        const char *EntitiesManagerException::what() const noexcept
        {
            return _message.c_str();
        }

        void EntitiesManager::update(double deltaTime)
        {
            auto inputField = getComponentsByType(Components::CompType::INPUTFIELD);
            auto trantorians = getEntitiesByType(EntityType::TRANTORIAN);
            auto expulsions = getEntitiesByType(EntityType::EXPULSION);
            auto buttons = getComponentsByType(Components::CompType::BUTTON);
            
            for (const auto &it : *inputField) {
                auto component = std::static_pointer_cast<Components::InputField>(it);
                component->update();
            }
            for (const auto &it : *buttons) {
                auto component = std::static_pointer_cast<Components::Button>(it);
                component->update();
            }
            for (auto &entity : _entities) {
                entity->update(deltaTime);
            }
            for (const auto &it : *trantorians) {
                auto entity =
                std::static_pointer_cast<Entities::Trantorian>(it);
                if (entity->getDispawned()) {
                    killEntityById(entity->getId());
                }
            }
            for (const auto &it : *expulsions) {
                auto entity =
                std::static_pointer_cast<Entities::Expulsion>(it);
                if (entity->getExpulsed()) {
                    killEntityById(entity->getId());
                }
            }
        }

        void EntitiesManager::addEntity(const std::shared_ptr<IEntity> &entity)
        {
            _entities.push_back(entity);
        }

        const std::vector<std::shared_ptr<IEntity>> &
        EntitiesManager::getEntities() const
        {
            return _entities;
        }

        std::shared_ptr<IEntity> EntitiesManager::getEntityById(
        const std::string &id) const
        {
            for (const auto &entity : _entities) {
                if (entity->getId() == id)
                    return entity;
            }
            throw EntitiesManagerException("No entity with this id");
        }

        std::unique_ptr<std::vector<std::shared_ptr<Components::IComponent>>>
        EntitiesManager::getComponentsByType(Components::CompType type) const
        {
            auto components = std::make_unique<
            std::vector<std::shared_ptr<Components::IComponent>>>();

            for (const auto &entity : _entities) {
                const auto &entityComponents =
                entity->getComponentsByType(type);
                for (const auto &component : *entityComponents) {
                    components->push_back(component);
                }
            }
            return components;
        }

        bool EntitiesManager::doesEntityExist(const std::string &id) const
        {
            for (const auto &entity : _entities) {
                if (entity->getId() == id) {
                    return true;
                }
            }
            return false;
        }

        std::unique_ptr<std::vector<std::shared_ptr<IEntity>>>
        EntitiesManager::getEntitiesByType(EntityType type) const
        {
            auto entities =
            std::make_unique<std::vector<std::shared_ptr<IEntity>>>();

            for (const auto &entity : _entities) {
                if (entity->getType() == type) {
                    entities->push_back(entity);
                }
            }
            return entities;
        }

        void EntitiesManager::killEntityById(const std::string &id)
        {
            for (auto iterator = _entities.begin(); iterator != _entities.end();
                 iterator++) {
                if ((*iterator)->getId() == id) {
                    _entities.erase(iterator);
                    return;
                }
            }
            throw EntitiesManagerException("No entity with this id");
        }

        void EntitiesManager::killAllEntities()
        {
            _entities.clear();
        }

        void EntitiesManager::killEntitiesByType(EntityType type)
        {
            for (auto iterator = _entities.begin(); iterator != _entities.end();
                 iterator++) {
                if ((*iterator)->getType() == type) {
                    _entities.erase(iterator);
                    return;
                }
            }
            throw EntitiesManagerException("No entity with this type");
        }

        std::vector<std::string> EntitiesManager::getPlayersIds() const
        {
            std::vector<std::string> playersIds;

            for (const auto &entity : _entities) {
                if (entity->getType() == EntityType::TRANTORIAN) {
                    playersIds.push_back(entity->getId());
                }
            }
            return playersIds;
        }
    } // namespace Entities
} // namespace GUI
