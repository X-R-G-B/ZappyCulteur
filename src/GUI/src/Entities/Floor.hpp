/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** Floor
*/

#pragma once

#include <vector>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "AEntity.hpp"
#include "Ressources.hpp"
#include "Sprite.hpp"

namespace GUI {
    namespace Entities {
        class Floor : public AEntity {
            public:
                Floor(const std::string &id,
                    const Vector2F &position,
                    unsigned int width = 20,
                    unsigned int height = 20,
                    float tileSize = 92
                );
                void createRessource(unsigned int x, unsigned int y, RessourcesType ressource);
                ~Floor() = default;
                void update() override;
            private:
                void initSprites();
                void initTexture();
                void createDarkFloor(unsigned int x, unsigned int y);
                void createLightFloor(unsigned int x, unsigned int y);
                sf::Texture _txFloorDark;
                sf::Texture _txFloorLight;          
                std::unordered_map<RessourcesType, sf::Texture> _ressources;
                unsigned int _width;
                unsigned int _height;
                float _tileSize;
        };
    }
}
