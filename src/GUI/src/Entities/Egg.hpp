/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** egg
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "AEntity.hpp"
#include "Sprite.hpp"

namespace GUI {
    namespace Entities {
        class Egg : public AEntity {
            public:
                Egg(const std::string &id, const Vector2F &position);
                ~Egg() = default;
                void update(double deltaTime) final;

            private:
                void initSprites();
                sf::Texture _texture;
        };
    } // namespace Entities
} // namespace GUI
