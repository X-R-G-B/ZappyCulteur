/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** HUD
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <chrono>
#include <memory>
#include <stdexcept>
#include "AEntity.hpp"
#include "EntitiesManager.hpp"
#include "Music.hpp"
#include "Sprite.hpp"
#include "Text.hpp"
#include "Trantorian.hpp"
#include "Vector2F.hpp"
#include <unordered_map>

namespace GUI {
    namespace Entities {

        class HUDException : public std::exception {
            public:
                HUDException(const std::string &msg);
                const char *what() const noexcept final;

            private:
                std::string _msg;
        };

        class HUD : public AEntity {
            public:
                HUD(const std::string &id,
                std::shared_ptr<Entities::EntitiesManager> &entitiesManager);
                ~HUD() = default;
                void update(double deltaTime) final;

            private:
                void createSelectedSprite();
                void removeSelectedSprite();
                void updateSelectedTile();
                void removeInfoTexts();
                void updateCounterBox();
                void initTextures();
                void initMaintThemeMusic();
                unsigned int getRessourceAmount(
                RessourcesType type, Vector2F tile);
                void createQuantityText(
                const std::string &id, const Vector2F &pos);
                void createSelectedTexts();
                std::unordered_map<GUI::Entities::RessourcesType,
                Components::Text>
                _ressourcesTexts;
                sf::Texture _txTileInfos;
                sf::Texture _txSelectedTile;
                sf::Sprite _tileInfoSprite;
                sf::Sprite _selectedTileSprite;
                Vector2F _selectedTile;
                bool _isTileSelected = false;
                std::shared_ptr<Entities::EntitiesManager> _entitiesManager;
        };
    } // namespace Entities
} // namespace GUI
