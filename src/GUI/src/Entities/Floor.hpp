/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** Floor
*/

#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "AEntity.hpp"
#include "Sprite.hpp"

#define TILE_SIZE 92

namespace GUI {
    namespace Entities {
        class Floor : public AEntity {
            public:
                Floor(const std::string &id,
                    const Vector2F &position,
                    unsigned int width = 20,
                    unsigned int height = 20,
                    float tileSize = TILE_SIZE
                );
                ~Floor() = default;
                void update() override;
            private:
                void initSprites();
                void initTexture();
                void createDarkFloor(unsigned int x, unsigned int y);
                void createLightFloor(unsigned int x, unsigned int y);
                sf::Texture _txFloorDark;
                sf::Texture _txFloorLight;
                unsigned int _width;
                unsigned int _height;
                float _tileSize;
        };
    }
}
