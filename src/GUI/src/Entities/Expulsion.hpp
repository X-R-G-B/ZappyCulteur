/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** Expulsion
*/

#pragma once

#include <chrono>
#include "AEntity.hpp"

namespace GUI {
    namespace Entities {
        class Expulsion : public AEntity {
            public:
                Expulsion(const std::string &id, const Vector2F &position,
                    EntityOrientation orientations, unsigned int width = 0,
                            unsigned int height = 0);
                ~Expulsion();

                void update(double deltaTime) final;

                void initExpulsionSprite();

                bool getExpulsed();
            protected:
            private:
                sf::Texture _texture;
                unsigned int _width;
                unsigned int _height;
                bool _isExpulsed;
                std::chrono::seconds _timeDispawn;
                std::chrono::time_point<std::chrono::system_clock> _deathClock;
        };
    }
}