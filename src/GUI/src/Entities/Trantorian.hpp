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
                    const Vector2F &position,
                    EntityOrientation orientation,
                    size_t level
                );
                ~Trantorian() = default;
                void update(double deltaTime) final;
                void setLevel(int level);
                const std::size_t &getLevel() const;
                void setTeam(const std::string &team);
                const std::string &getTeam() const;
                void setToGo(const Vector2F &toGo);

            private:
                void initSprites();
                size_t _level;
                std::string _team;
                sf::Texture _texture;
                Vector2F _direction;
                Vector2F _toGo;
                float _speed;
        };
    }
}
