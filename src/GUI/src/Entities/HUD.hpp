/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** HUD
*/

#pragma once

#include <chrono>
#include <SFML/Graphics.hpp>
#include <memory>
#include "Trantorian.hpp"
#include "Sprite.hpp"
#include "AEntity.hpp"
#include "Vector2F.hpp"
#include "EntitiesManager.hpp"

namespace GUI {
    namespace Entities {
        class HUD : public AEntity {
            public:
                HUD(
                    const std::string &id,
                    std::shared_ptr<Entities::EntitiesManager> &entitiesManager
                );
                ~HUD() = default;
                void update(double deltaTime) final;

            private:
                void createSelectedSprite();
                void removeSelectedSprite();
                void updateInfosSprite();
                void initTextures();
                sf::Texture _txTileInfos;
                sf::Texture _txSelectedTile;
                sf::Sprite _tileInfoSprite;
                sf::Sprite _selectedTileSprite;
                Vector2F _selectedTile;
                bool _isTileSelected = false;
                std::shared_ptr<Entities::EntitiesManager> _entitiesManager;
        };
    }
}
