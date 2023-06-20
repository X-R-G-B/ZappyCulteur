/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** EndScreen
*/

#pragma once

#include "Sprite.hpp"
#include "AEntity.hpp"

namespace GUI {
    namespace Entities {
        class EndScreen : public AEntity {
            public:
                EndScreen(const std::string &id,
                            const Vector2F &position,
                            const std::string &teamName = "NONE",
                            unsigned int width = 1920,
                            unsigned int height = 1080,
                            EntityOrientation orientation = EntityOrientation::UP);
                ~EndScreen();

                void update(double deltaTime) final;

                void initEndScreenSprite();
            protected:
            private:
                std::string _teamName;
                sf::Texture _texture;
                unsigned int _width;
                unsigned int _height;
        };
    }
}
