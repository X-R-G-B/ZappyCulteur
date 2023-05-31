/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** CompQuery
*/

#pragma once

#include <map>
#include <SFML/Graphics.hpp>
#include "IComponent.hpp"
#include "IEntity.hpp"
#include "Sprite.hpp"

namespace GUI {
    namespace Components {
        class CompQuery {
            public:
                CompQuery(const std::vector<std::shared_ptr<GUI::Entities::IEntity>> &entities)
                    : _entities(entities) {}
                ~CompQuery() = default;

                std::unique_ptr<std::map<size_t, std::vector<std::shared_ptr<GUI::Components::Sprite>>>> getSpritesFromEntities()
                {
                    auto sprites = std::make_unique<std::map<size_t, std::vector<std::shared_ptr<GUI::Components::Sprite>>>>();

                    for (const auto& entity : _entities) {
                        const auto& spriteComps = entity->getComponentsByType(CompType::SPRITE);
                        for (const auto& spriteComp : *spriteComps) {
                            auto sprite = std::dynamic_pointer_cast<GUI::Components::Sprite>(spriteComp);
                            if (sprite != nullptr) {
                                auto layer = sprite->getLayer();
                                (*sprites)[layer].push_back(sprite);
                            }
                        }
                    }
                    return sprites;
                }

            private:
                const std::vector<std::shared_ptr<GUI::Entities::IEntity>> &_entities;
        };
    }
}
