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
            unsigned int height) :
            _width(width),
            _height(height)
        {
            _id = id;
            _type = EntityType::ENVIROMENT;
            _position = position;
            _rotation = Vector2F(0, 0);
            _scale = Vector2F(1, 1);
            initSprites();
        }

        void Floor::update()
        {
        }

        void Floor::initTexture()
        {
            if (_txFloorDark.loadFromFile("assets/environment/darkFloor.png") == false ||
                _txFloorLight.loadFromFile("assets/environment/lightFloor.png") == false) {
                throw std::exception();
            }
        }

        void Floor::initSprites()
        {
            try {
                initTexture();
                float top = _position.y - (static_cast<float>(_height) / 2) * 92;
                float left = _position.x - (static_cast<float>(_width) / 2) * 92;
                for (int i = 0; i < _width; i++) {
                    for (int j = 0; j < _height; j++) {
                        if ((i + j) % 2 == 0) {
                            createDarkFloor(
                                Vector2F(left + i * 92, top + j * 92),
                                _id + std::to_string(i) + std::to_string(j)
                            );
                        } else {
                            createLightFloor(
                                Vector2F(left + i * 92, top + j * 92),
                                _id + std::to_string(i) + std::to_string(j)
                            );
                        }
                    }
                }
            } catch (const std::exception &e) {
                std::cerr << e.what() << std::endl;
            }
        }

        void Floor::createDarkFloor(Vector2F position, std::string id)
        {
            _components.push_back(std::make_shared<GUI::Components::Sprite>(
                id,
                _txFloorDark,
                10,
                Vector2F(position.x, position.y)
            ));
        }

        void Floor::createLightFloor(Vector2F position, std::string id)
        {
            _components.push_back(std::make_shared<GUI::Components::Sprite>(
                id,
                _txFloorLight,
                10,
                Vector2F(position.x, position.y)
            ));
        }
    }
}
