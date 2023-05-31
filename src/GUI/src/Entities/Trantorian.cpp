/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** Trantorian
*/

#include <iostream>
#include "Trantorian.hpp"

namespace GUI {
    namespace Entities {
        Trantorian::Trantorian(
            const std::string &id,
            const std::string &team,
            const Vector2F &position) :
            _level(1),
            _speed(5),
            _team(team)
        {
            _id = id;
            _type = EntityType::TRANTORIAN;
            _orientation = EntityOrientation::DOWN;
            _position = position;
            _rotation = Vector2F(0, 0);
            _scale = Vector2F(1, 1);
            initSprites();
        }

        void Trantorian::update()
        {
        }

        void Trantorian::setLevel(int level)
        {
            _level = level;
        }

        int Trantorian::getLevel() const
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
                _texture.loadFromFile("assets/bees/beeLeft.png");
                _components.push_back(std::make_shared<GUI::Components::Sprite>(
                    _id + "BodySprite",
                    _texture,
                    0,
                    _position
                ));
                _entityCompType.push_back(Components::CompType::SPRITE);
            } catch (std::exception &e) {
                std::cerr << e.what() << std::endl;
            }
        }
    }
}
