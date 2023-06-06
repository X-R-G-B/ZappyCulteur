/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** Floor
*/

#include <iostream>
#include "Floor.hpp"

namespace GUI {
    namespace Entities {
        Floor::Floor(
            const std::string &id,
            const Vector2F &position,
            unsigned int width,
            unsigned int height,
            float tileSize) :
            AEntity(
                id,
                position,
                Vector2F(0, 0),
                Vector2F(1, 1),
                EntityType::ENVIROMENT,
                EntityOrientation::RIGHT
            ),
            _width(width),
            _height(height),
            _tileSize(tileSize)
        {
            initSprites();
        }

        void Floor::update(double)
        {
        }

        void Floor::initTexture()
        {
            if (_txFloorDark.loadFromFile("src/GUI/assets/environment/darkFloor.png") == false ||
                _txFloorLight.loadFromFile("src/GUI/assets/environment/lightFloor.png") == false) {
                throw EntityException("Error: could not load floor texture");
            }
        }

        void Floor::initSprites()
        {
            try {
                initTexture();
            } catch (const EntityException &e) {
                std::cerr << e.what() << std::endl;
                return;
            }
            for (unsigned int i = 0; i < _width; i++) {
                for (unsigned int j = 0; j < _height; j++) {
                    if ((i + j) % 2 == 0) {
                        createDarkFloor(i, j);
                    } else {
                        createLightFloor(i, j);
                    }
                }
            }
        }

        void Floor::createDarkFloor(unsigned int i, unsigned int j)
        {
            std::string id = _id + std::to_string(i) + std::to_string(j);

            _components.push_back(std::make_shared<GUI::Components::Sprite>(
                id,
                _txFloorDark,
                10,
                Vector2F(
                    _tileSize * static_cast<float>(i),
                    _tileSize * static_cast<float>(j)
                ),
                _tileSize,
                _tileSize
            ));
        }

        void Floor::createLightFloor(unsigned int i, unsigned int j)
        {
            std::string id = _id + std::to_string(i) + std::to_string(j);

            _components.push_back(std::make_shared<GUI::Components::Sprite>(
                id,
                _txFloorLight,
                10,
                Vector2F(
                    _tileSize * static_cast<float>(i),
                    _tileSize * static_cast<float>(j)
                ),
                _tileSize,
                _tileSize
            ));
        }
    }
}
