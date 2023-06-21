/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** CompQuery
*/

#include "CompQuery.hpp"

namespace GUI {
    namespace Components {

        void CompQuery::sortSpritesByLayer(
        std::unique_ptr<std::vector<std::shared_ptr<Components::IComponent>>>
        &sprites)
        {
            std::sort(sprites->begin(), sprites->end(),
            [](const std::shared_ptr<Components::IComponent> &a,
            const std::shared_ptr<Components::IComponent> &b) {
                const auto &firstSprite =
                std::static_pointer_cast<Components::Sprite>(a);
                const auto &secondSprite =
                std::static_pointer_cast<Components::Sprite>(b);
                return firstSprite->getLayer() < secondSprite->getLayer();
            });
        }

    } // namespace Components
} // namespace GUI
