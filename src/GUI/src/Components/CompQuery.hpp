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
                CompQuery() = default;
                ~CompQuery() = default;

                void sortSpritesByLayer(std::unique_ptr<std::vector<std::shared_ptr<Components::IComponent>>> &sprites);

        };
    }
}
