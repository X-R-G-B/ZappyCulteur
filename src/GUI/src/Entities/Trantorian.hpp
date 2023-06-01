/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** Trantorian
*/

#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "AEntity.hpp"
#include "Sprite.hpp"

namespace GUI {
    namespace Entities {
        class Trantorian : public AEntity {
            public:
                Trantorian(const std::string &id,
                    const std::string &team,
                    const Vector2F &position
                );
                ~Trantorian() = default;
                void update() final;
                void setLevel(int level);
                const std::size_t &getLevel() const;
                void setTeam(const std::string &team);
                const std::string &getTeam() const;

            private:
                void initSprites();
                size_t _level;
                std::string _team;
                sf::Texture _texture;
                Vector2F _direction;
                float _speed;
        };
    }
}
