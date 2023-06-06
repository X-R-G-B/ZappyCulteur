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
        static const std::string food = "_FOOD";
        static const std::string linemate = "_LINEMATE";
        static const std::string deraumere = "_DERAUMERE";
        static const std::string sibur = "_SIBUR";
        static const std::string mendiane = "_MENDIANE";
        static const std::string phiras = "_PHIRAS";
        static const std::string thystame = "_THYSTAME";

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

        void Floor::update()
        {
        }

        void Floor::initTexture()
        {
            if (_txFloorDark.loadFromFile("src/GUI/assets/environment/darkFloor.png") == false ||
                _txFloorLight.loadFromFile("src/GUI/assets/environment/lightFloor.png") == false ||
                _txFood.loadFromFile("src/GUI/assets/environment/honey.png") == false ||
                _txLinemate.loadFromFile("src/GUI/assets/environment/rocks.png") == false ||
                _txDeraumere.loadFromFile("src/GUI/assets/environment/flower.png") == false ||
                _txSibur.loadFromFile("src/GUI/assets/environment/rose.png") == false ||
                _txMendiane.loadFromFile("src/GUI/assets/environment/hibiscus.png") == false ||
                _txPhiras.loadFromFile("src/GUI/assets/environment/camellia.png") == false ||
                _txThystame.loadFromFile("src/GUI/assets/environment/dahlia.png") == false) {
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

        void Floor::createFood(unsigned int x, unsigned int y)
        {
            std::string id = std::to_string(x) + std::to_string(y) + food;

            _components.push_back(std::make_shared<GUI::Components::Sprite>(
                id,
                _txFood,
                20,
                Vector2F(
                    _tileSize * static_cast<float>(x),
                    _tileSize * static_cast<float>(y)
                ),
                _tileSize,
                _tileSize
            ));
        }

        void Floor::createLinemate(unsigned int x, unsigned int y)
        {
            std::string id = std::to_string(x) + std::to_string(y) + linemate;

            _components.push_back(std::make_shared<GUI::Components::Sprite>(
                id,
                _txLinemate,
                20,
                Vector2F(
                    _tileSize * static_cast<float>(x),
                    _tileSize * static_cast<float>(y)
                ),
                _tileSize,
                _tileSize
            ));
        }

        void Floor::createDeraumere(unsigned int x, unsigned int y)
        {
            std::string id = std::to_string(x) + std::to_string(y) + deraumere;

            _components.push_back(std::make_shared<GUI::Components::Sprite>(
                id,
                _txDeraumere,
                20,
                Vector2F(
                    _tileSize * static_cast<float>(x),
                    _tileSize * static_cast<float>(y)
                ),
                _tileSize,
                _tileSize
            ));
        }

        void Floor::createSibur(unsigned int x, unsigned int y)
        {
            std::string id = std::to_string(x) + std::to_string(y) + sibur;

            _components.push_back(std::make_shared<GUI::Components::Sprite>(
                id,
                _txSibur,
                20,
                Vector2F(
                    _tileSize * static_cast<float>(x),
                    _tileSize * static_cast<float>(y)
                ),
                _tileSize,
                _tileSize
            ));
        }

        void Floor::createMendiane(unsigned int x, unsigned int y)
        {
            std::string id = std::to_string(x) + std::to_string(y) + mendiane;

            _components.push_back(std::make_shared<GUI::Components::Sprite>(
                id,
                _txMendiane,
                20,
                Vector2F(
                    _tileSize * static_cast<float>(x),
                    _tileSize * static_cast<float>(y)
                ),
                _tileSize,
                _tileSize
            ));
        }

        void Floor::createPhiras(unsigned int x, unsigned int y)
        {
            std::string id = std::to_string(x) + std::to_string(y) + phiras;

            _components.push_back(std::make_shared<GUI::Components::Sprite>(
                id,
                _txPhiras,
                20,
                Vector2F(
                    _tileSize * static_cast<float>(x),
                    _tileSize * static_cast<float>(y)
                ),
                _tileSize,
                _tileSize
            ));
        }

        void Floor::createThystame(unsigned int x, unsigned int y)
        {
            std::string id = std::to_string(x) + std::to_string(y) + thystame;

            _components.push_back(std::make_shared<GUI::Components::Sprite>(
                id,
                _txThystame,
                20,
                Vector2F(
                    _tileSize * static_cast<float>(x),
                    _tileSize * static_cast<float>(y)
                ),
                _tileSize,
                _tileSize
            ));
        }

        void Floor::createDarkFloor(unsigned int x, unsigned int y)
        {
            std::string id = _id + std::to_string(x) + std::to_string(y);

            _components.push_back(std::make_shared<GUI::Components::Sprite>(
                id,
                _txFloorDark,
                10,
                Vector2F(
                    _tileSize * static_cast<float>(x),
                    _tileSize * static_cast<float>(y)
                ),
                _tileSize,
                _tileSize
            ));
        }

        void Floor::createLightFloor(unsigned int x, unsigned int y)
        {
            std::string id = _id + std::to_string(x) + std::to_string(y);

            _components.push_back(std::make_shared<GUI::Components::Sprite>(
                id,
                _txFloorLight,
                10,
                Vector2F(
                    _tileSize * static_cast<float>(x),
                    _tileSize * static_cast<float>(y)
                ),
                _tileSize,
                _tileSize
            ));
        }
    }
}
