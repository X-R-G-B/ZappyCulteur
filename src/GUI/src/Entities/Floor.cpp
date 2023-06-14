/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** Floor
*/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Floor.hpp"

namespace GUI {
    namespace Entities {

        static const std::unordered_map<RessourcesType, std::string> idOfRessources = {
            {RessourcesType::FOOD, "_FOOD"},
            {RessourcesType::LINEMATE, "_LINEMATE"},
            {RessourcesType::DERAUMERE, "_DERAUMERE"},
            {RessourcesType::SIBUR, "_SIBUR"},
            {RessourcesType::MENDIANE, "_MENDIANE"},
            {RessourcesType::PHIRAS, "_PHIRAS"},
            {RessourcesType::THYSTAME, "_THYSTAME"}
        };

        static const std::unordered_map<RessourcesType, std::string> pathToData = {
            {RessourcesType::FOOD, "src/GUI/assets/environment/honey.png"},
            {RessourcesType::LINEMATE, "src/GUI/assets/environment/rocks.png"},
            {RessourcesType::DERAUMERE, "src/GUI/assets/environment/flower.png"},
            {RessourcesType::SIBUR, "src/GUI/assets/environment/rose.png"},
            {RessourcesType::MENDIANE, "src/GUI/assets/environment/hibiscus.png"},
            {RessourcesType::PHIRAS, "src/GUI/assets/environment/camellia.png"},
            {RessourcesType::THYSTAME, "src/GUI/assets/environment/camellia.png"}
        };

        static const std::size_t ressourceLayer = 20;
        static const std::string darkFloorPath = "src/GUI/assets/environment/darkFloor.png";
        static const std::string lightFloorPath = "src/GUI/assets/environment/lightFloor.png";

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
            if (_txFloorDark.loadFromFile(darkFloorPath) == false ||
                _txFloorLight.loadFromFile(lightFloorPath) == false) {
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

        void Floor::createRessources(
            unsigned int x,
            unsigned int y,
            RessourcesType ressource,
            unsigned int quantity)
        {
            std::string id = std::to_string(x) + std::to_string(y) + idOfRessources.at(ressource);

            for (auto itComponents = _components.begin(); itComponents != _components.end(); itComponents++) {
                auto entity = std::static_pointer_cast<Components::Sprite>(*itComponents);
                if (entity == nullptr) {
                    continue;
                }
                auto entityId = entity->getId();
                if (entityId == id) {
                    quantity -= 1;
                }
            }
            for (unsigned int i = 0; i < quantity; i++) {
                createRessource(x, y, ressource);
            }
        }

        void Floor::removeRessources(Vector2F tile, RessourcesType ressource)
        {
            int x = static_cast<int>(tile.x);
            int y = static_cast<int>(tile.y);
            std::string id = std::to_string(x) + std::to_string(y) + idOfRessources.at(ressource);

            for (auto itComponents = _components.begin(); itComponents != _components.end(); itComponents++) {
                auto entity = std::static_pointer_cast<Components::Sprite>(*itComponents);
                auto entityId = entity->getId();
                if (entityId == id) {
                    _components.erase(itComponents);
                    return;
                }
            }
        }

        void Floor::loadRessourceTexture(RessourcesType ressource)
        {
            sf::Texture tx;

            auto search = _ressources.find(ressource);
            if (search == _ressources.end()) {
                if (tx.loadFromFile(pathToData.find(ressource)->second) == false) {
                    return;
                } else {
                    _ressources.emplace(std::make_pair(ressource, tx));
                }
            } else {
                tx = search->second;
            }
        }

        void Floor::createRessource(unsigned int x, unsigned int y, RessourcesType ressource)
        {
            std::string id = std::to_string(x) + std::to_string(y) + idOfRessources.at(ressource);
            float ressourceSize = computeRessourceSize();
            Vector2F ressourcePos = computeRessourcePosition(x, y, ressourceSize);

            loadRessourceTexture(ressource);
            _components.push_back(std::make_shared<GUI::Components::Sprite>(
                id,
                _ressources.find(ressource)->second,
                ressourceLayer,
                ressourcePos,
                ressourceSize,
                ressourceSize
            ));
        }

        float Floor::computeRessourceSize()
        {
            float size = rand() % static_cast<int>(_maxRessourceSize - _minRessourceSize + 1) + _minRessourceSize;
            return (size);
        }

        Vector2F Floor::computeRessourcePosition(
            unsigned int x,
            unsigned int y,
            float ressourceSize)
        {
            int offset = static_cast<int>(_tileSize - ressourceSize);
            int offsetX = static_cast<int>(_tileSize * static_cast<float>(x));
            int offsetY = static_cast<int>(_tileSize * static_cast<float>(y));

            float posX = static_cast<float>(rand() % offset + offsetX);
            float posY = static_cast<float>(rand() % offset + offsetY);
            return (Vector2F(posX, posY));
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
