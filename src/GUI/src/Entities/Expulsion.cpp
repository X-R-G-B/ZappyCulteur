/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** Expulsion
*/

#include <iostream>
#include "Expulsion.hpp"
#include "Components/Sprite.hpp"
#include "EntitiesManager.hpp"

static const std::string expulsionPath = "src/GUI/assets/environment/Explosion-PNG-HD.png";
static const std::size_t expulsionLayer = 100;

namespace GUI {
    namespace Entities {
        Expulsion::Expulsion(const std::string &id,
                                const Vector2F &position,
                                EntityOrientation orientation,
                                unsigned int width,
                                unsigned int height)
            : AEntity(
                id,
                position,
                Vector2F(0, 0),
                Vector2F(1, 1),
                EntityType::EXPULSION,
                orientation
            ),
            _width(width),
            _height(height),
            _isExpulsed(false),
            _timeDispawn(2)
        {
            _deathClock = std::chrono::system_clock::now();
        }

        Expulsion::~Expulsion()
        {
        }

        void Expulsion::update([[maybe_unused]]double deltaTime)
        {
            auto currentTime = std::chrono::system_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(
            currentTime - _deathClock);
            if (_timeDispawn <= elapsed) {
                _isExpulsed = true;
                return;
            }
        }

        void initExpulsionClock()
        {
        }

        void Expulsion::initExpulsionSprite()
        {
            try {
                _texture.loadFromFile(expulsionPath);
                _components.push_back(std::make_shared<GUI::Components::Sprite>(
                _id, _texture, expulsionLayer, _position, _width,
                _height));
            } catch (std::exception &e) {
                std::cerr << e.what() << std::endl;
                throw EntitiesManagerException("Sprite error");
            }
        }

        bool Expulsion::getExpulsed()
        {
            return (_isExpulsed);
        }

    }
}