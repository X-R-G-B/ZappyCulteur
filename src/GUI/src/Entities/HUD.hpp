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
#include <unordered_map>
#include "Trantorian.hpp"
#include "Sprite.hpp"
#include "AEntity.hpp"
#include "Vector2F.hpp"
#include "EntitiesManager.hpp"
#include "Text.hpp"

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
                void updateSelectedTile();
                void removeInfoTexts();
                void updateCounterBox();
                void initTextures();
                unsigned int getRessourceAmount(RessourcesType type, Vector2F tile);
                void createQuantityText(const std::string &id, RessourcesType type, Vector2F pos);
                std::unordered_map<GUI::Entities::RessourcesType, Components::Text> _ressourcesTexts;
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
