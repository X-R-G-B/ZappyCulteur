/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** CompQuery
*/


#include "CompQuery.hpp"

namespace GUI {
    namespace Components {

        std::unique_ptr<std::map<size_t, std::vector<std::shared_ptr<GUI::Components::Sprite>>>>
            CompQuery::sortSpritesByLayer(std::unique_ptr<std::vector<std::shared_ptr<Components::IComponent>>> sprites)
        {
            auto sortedSprites = std::make_unique<std::map<size_t, std::vector<std::shared_ptr<GUI::Components::Sprite>>>>();
            
            for (auto &sprite : *sprites) {
                auto spritePtr = std::static_pointer_cast<GUI::Components::Sprite>(sprite);
                if (spritePtr == nullptr) {
                    continue;
                }
                if (sortedSprites->find(spritePtr->getLayer()) == sortedSprites->end()) {
                    sortedSprites->insert(
                        std::make_pair(spritePtr->getLayer(), std::vector<std::shared_ptr<GUI::Components::Sprite>>())
                    );
                }
                sortedSprites->at(spritePtr->getLayer()).push_back(spritePtr);
            }
            return sortedSprites;
        }

    }
}
