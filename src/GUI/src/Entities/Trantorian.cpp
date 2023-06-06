/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** Trantorian
*/

#include <iostream>
#include "Trantorian.hpp"
#include "Components/Sprite.hpp"

namespace GUI {
    namespace Entities {
        Trantorian::Trantorian(
            const std::string &id,
            const std::string &team,
            const Vector2F &position,
            EntityOrientation orientation,
            size_t level) :
            AEntity(
                id,
                position,
                Vector2F(0, 0),
                Vector2F(1, 1),
                EntityType::TRANTORIAN,
                orientation
            ),
            _level(level),
            _team(team),
            _speed(200),
            _toGo(position)
        {
            initSprites();
        }

        void Trantorian::update(double deltaTime)
        {
            if (_toGo.x != _position.x || _toGo.y != _position.y) {
                auto direction = _toGo - _position;
                auto distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
                auto normalized = direction / distance;
                auto movement = normalized * _speed * deltaTime;
                if (std::abs(movement.x) > std::abs(direction.x) ||
                    std::abs(movement.y) > std::abs(direction.y)) {
                    _position = _toGo;
                } else {
                    _position += movement;
                }
            }
            for (auto &comp : _components) {
                if (comp->getType() == Components::CompType::SPRITE) {
                    auto sprite = std::static_pointer_cast<GUI::Components::Sprite>(comp);
                    sprite->setPosition({_position.x, _position.y});
                }
            }
        }

        void Trantorian::setLevel(int level)
        {
            _level = level;
        }

        const std::size_t &Trantorian::getLevel() const
        {
            return _level;
        }

        void Trantorian::setTeam(const std::string &team)
        {
            _team = team;
        }

        const std::string &Trantorian::getTeam() const
        {
            return _team;
        }

        void Trantorian::setToGo(const Vector2F &toGo)
        {
            _toGo = toGo;
        }

        void Trantorian::initSprites()
        {
            try {
                _texture.loadFromFile("src/GUI/assets/bees/beeLeft.png");
                _components.push_back(std::make_shared<GUI::Components::Sprite>(
                    _id + "BodySprite",
                    _texture,
                    50,
                    _position,
                    92,
                    92
                ));
                _entityCompType.push_back(Components::CompType::SPRITE);
            } catch (std::exception &e) {
                std::cerr << e.what() << std::endl;
            }
        }
    }
}
