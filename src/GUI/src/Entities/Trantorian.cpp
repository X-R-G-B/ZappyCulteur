/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** Trantorian
*/

#include <iostream>
#include <cmath>
#include "Trantorian.hpp"
#include "Components/Sprite.hpp"
#include "../Components/Color.hpp"

namespace GUI {
    namespace Entities {
        static const std::string beePath = "src/GUI/assets/bees/beeLeft.png";
        static const std::string bodySpriteSuffix = "BodySprite";
        static const std::string levelTextSuffix = "LevelText";
        static const std::size_t beeLayer = 50;
        static const unsigned int beeWidth = 92;
        static const unsigned int beeHeight = 92;
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
            _toGo(position),
            _speed(beeSpeed),
            _isDead(false),
            _timeDispawn(beeAnimationDead)
        {
            initSprites();
            createTextComponent();
        }

        void Trantorian::initDeathClock()
        {
            if (_deathClock == std::chrono::time_point<std::chrono::system_clock>{}) {
                _deathClock = std::chrono::system_clock::now();
            }
        }

        void Trantorian::update(double deltaTime)
        {
            if (_isDead) {
                initDeathClock();
                auto currentTime = std::chrono::system_clock::now();
                auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(currentTime - _deathClock);
                if (_timeDispawn <= elapsed) {
                    _isDispawned = true;
                    return;
                }
            }
            updatePosition(deltaTime);
            updateComponents();
        }

        void Trantorian::updatePosition(double deltaTime)
        {
            if (_toGo.x != _position.x || _toGo.y != _position.y) {
                auto direction = _toGo - _position;
                auto distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
                auto normalized = direction / distance;
                auto movement = normalized * _speed * static_cast<float>(deltaTime);
                if (std::abs(movement.x) > std::abs(direction.x) ||
                    std::abs(movement.y) > std::abs(direction.y)) {
                    _position = _toGo;
                } else {
                    _position += movement;
                }
            }
        }

        void Trantorian::updateComponents()
        {
            for (auto &comp : _components) {
                switch (comp->getType()) {
                    case Components::CompType::SPRITE: {
                        auto sprite = std::static_pointer_cast<GUI::Components::Sprite>(comp);
                        sprite->setPosition({_position.x, _position.y});
                        break;
                    }
                    case Components::CompType::TEXT: {
                        auto text = std::static_pointer_cast<GUI::Components::Text>(comp);
                        text->setPosition({_position.x, _position.y - levelYOffset});
                        break;
                    }
                    default:
                        break;
                }
            }
        }

        void Trantorian::setLevel(int level)
        {
            _level = level;
            for (auto &comp : _components) {
                if (comp->getType() == Components::CompType::TEXT) {
                    auto text = std::static_pointer_cast<GUI::Components::Text>(comp);
                    if (text->getId() == _id + levelTextSuffix) {
                        text->setText(std::to_string(_level));
                    }
                }
            }
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

        void Trantorian::setDead(bool dispawn)
        {
            _isDead = dispawn;
        }

        bool Trantorian::getDead()
        {
            return (_isDead);
        }

        bool Trantorian::getDispawned()
        {
            return (_isDispawned);
        }

        void Trantorian::setDispawned(bool dispawn)
        {
            _isDispawned = dispawn;
        }

        const std::chrono::seconds Trantorian::getDispawnTime()
        {
            return (_timeDispawn);
        }

        void Trantorian::initSprites()
        {
            try {
                _texture.loadFromFile(beePath);
                _components.push_back(std::make_shared<GUI::Components::Sprite>(
                    _id + bodySpriteSuffix,
                    _texture,
                    beeLayer,
                    _position,
                    beeWidth,
                    beeHeight
                ));
                _entityCompType.push_back(Components::CompType::SPRITE);
            } catch (std::exception &e) {
                std::cerr << e.what() << std::endl;
            }
        }

        void Trantorian::createTextComponent()
        {
            GUI::Color color(255, 255, 0, 255);

            _components.push_back(std::make_shared<GUI::Components::Text>(
                _id + levelTextSuffix,
                std::to_string(_level),
                Vector2F(_position.x, _position.y - levelYOffset),
                color,
                levelFontSize
            ));
            _entityCompType.push_back(Components::CompType::SPRITE);
        }
    }
}
