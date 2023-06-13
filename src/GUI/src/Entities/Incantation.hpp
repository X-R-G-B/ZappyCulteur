/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** Incantation
*/

#pragma once

#include <chrono>
#include "Trantorian.hpp"
#include "Sprite.hpp"
#include "AEntity.hpp"

namespace GUI {
    namespace Entities {
        class Incantation : public AEntity {
            public:
                Incantation(const std::string &id,
                    const Vector2F &position,
                    EntityOrientation orientations);
                ~Incantation();
                void update(double deltaTime) final;
                void endIncantation(int result);
                void addTrantorian(std::shared_ptr<Trantorian> trantorian);
            protected:
            private:
                void initIncantationSprite();
                void updateSpriteRect();
                sf::Texture _texture;
                std::vector<std::shared_ptr<Trantorian>> _trantorians;
                double _timeSinceLastRectChange;
        };
    }
}
