/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** Incantation
*/

#pragma once

#include <chrono>
#include "AEntity.hpp"
#include "Sprite.hpp"
#include "Trantorian.hpp"

namespace GUI {
    namespace Entities {
        class Incantation : public AEntity {
            public:
                Incantation(const std::string &id, const Vector2F &position,
                EntityOrientation orientations);
                ~Incantation();
                void update(double deltaTime) final;
                void endIncantation(std::size_t result);
                void addTrantorian(std::shared_ptr<Trantorian> trantorian);

            protected:
            private:
                void initIncantationSprite();
                void updateSpriteRect();
                sf::Texture _texture;
                std::vector<std::shared_ptr<Trantorian>> _trantorians;
                double _timeSinceLastRectChange;
        };
    } // namespace Entities
} // namespace GUI
