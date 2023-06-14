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
                /**
                 * @brief Create ressources on the floor
                 * 
                 * @param x the tile of number x
                 * @param y the tile of number y
                 * @param ressource the type of ressource
                 * @param quantity the quantity of ressource
                 */
                void createRessources(unsigned int x, unsigned int y, RessourcesType ressource, unsigned int quantity);
                
                /**
                 * @brief Create a ressource on the floor
                 * 
                 * @param x the tile of number x
                 * @param y the tile of number y
                 * @param ressource the type of ressource
                 */
                void createRessource(unsigned int x, unsigned int y, RessourcesType ressource);

                /**
                 * @brief Remove ressources on the floor
                 * 
                 * @param x the tile of number x
                 * @param y the tile of number y
                 * @param ressource the type of ressource
                 */
                void removeRessources(Vector2F tile, RessourcesType ressource);
                ~Floor() = default;
                void update(double deltaTime) override;
            private:
                void loadRessourceTexture(RessourcesType ressource);
                void initSprites();
                void initTexture();
                void createDarkFloor(unsigned int x, unsigned int y);
                void createLightFloor(unsigned int x, unsigned int y);
                float computeRessourceSize();
                Vector2F computeRessourcePosition(unsigned int x, unsigned int y, float ressourceSize);
                sf::Texture _txFloorDark;
                sf::Texture _txFloorLight;          
                std::unordered_map<RessourcesType, sf::Texture> _ressources;
                unsigned int _width;
                unsigned int _height;
                float _tileSize;
                static constexpr float _maxRessourceSize = TILE_SIZE / 2;
                static constexpr float _minRessourceSize = TILE_SIZE / 6;
        };
    }
}
