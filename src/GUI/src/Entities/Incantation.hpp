/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** Incantation
*/

#pragma once

#include "Trantorian.hpp"
#include "Sprite.hpp"
#include "AEntity.hpp"

namespace GUI {
    namespace Entities {
        class Incantation : public AEntity {
            public:
                Incantation(const std::string &id,
                    const Vector2F &position,
                    EntityOrientation orientation,
                    std::vector<std::shared_ptr<Trantorian>> &trantorians);
                ~Incantation();
                void update(double deltaTime) final;
                void endIncantation(bool result);
            protected:
            private:
                sf::Texture _texture; // sprite texture of incantation
                std::vector<std::shared_ptr<Trantorian>> _trantorians;
        };
    }
}
