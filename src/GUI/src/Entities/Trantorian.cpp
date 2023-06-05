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
            const Vector2F &position) :
            AEntity(
                id,
                position,
                Vector2F(0, 0),
                Vector2F(1, 1),
                EntityType::TRANTORIAN,
                EntityOrientation::RIGHT
            ),
            _level(1),
            _team(team),
            _speed(5)
        {
            initSprites();
        }

        void Trantorian::update()
        {
            if (_orientation == EntityOrientation::RIGHT) {
                if (_position.x < 1920 - 50) {
                    _position.x += _speed;
                } else {
                    _orientation = EntityOrientation::LEFT;
                }
            } else {
                if (_position.x >= 0) {
                    _position.x -= _speed;
                } else {
                    _orientation = EntityOrientation::RIGHT;
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
