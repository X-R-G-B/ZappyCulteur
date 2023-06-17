/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** HUD
*/

#include "Components/Sprite.hpp"
#include "HUD.hpp"
#include "Floor.hpp"
#include "EventsManager.hpp"
#include "Floor.hpp"
#include <iostream>

static const GUI::Vector2F HUD_SCALE = {1, 1};
static const GUI::Vector2F HUD_ROTATION = {0, 0};
static const GUI::Vector2F HUD_POSITION = {0, 0};

static const std::unordered_map<GUI::Entities::RessourcesType, std::string> ressourcesInfosId = {
    {GUI::Entities::RessourcesType::FOOD, "counterFoodTxt"},
    {GUI::Entities::RessourcesType::LINEMATE, "counterLinemateTxt"},
    {GUI::Entities::RessourcesType::DERAUMERE, "counterDeraumereTxt"},
    {GUI::Entities::RessourcesType::SIBUR, "counterSiburTxt"},
    {GUI::Entities::RessourcesType::MENDIANE, "counterMendianeTxt"},
    {GUI::Entities::RessourcesType::PHIRAS, "counterPhirasTxt"},
    {GUI::Entities::RessourcesType::THYSTAME, "counterThystameTxt"}
};

static const std::size_t selectedLayer = 150;
static const std::size_t tileInfosLayer = 200;

static const std::string selectedSpritePath = "src/GUI/assets/environment/selected.png";
static const std::string tileInfoSpritePath = "src/GUI/assets/UI/tileInfos.png";
static const std::string tileInfoSpriteId = "tileInfoSprite";
static const std::string selectedTileSpriteId = "selectedTileSprite";
static constexpr float tileSize = 92.0f;
static constexpr unsigned int infoWidth = 212;
static constexpr unsigned int infoHeight = 288;
static constexpr float margin = 20.0f;
static constexpr float marginBetweenTexts = 15.0f;

namespace GUI {
    namespace Entities {
        HUD::HUD(
            const std::string &id,
            std::shared_ptr<Entities::EntitiesManager> &entitiesManager)
            : AEntity(id,
                HUD_POSITION,
                HUD_ROTATION,
                HUD_SCALE,
                EntityType::HUD,
                EntityOrientation::UP
            ),
            _selectedTile(HUD_POSITION),
            _isTileSelected(false),
            _entitiesManager(entitiesManager)
        {
            _entityCompType.push_back(Components::CompType::HUDSPRITE);
            initTextures();
        }

        void HUD::update(double)
        {
            EventsManager &events = EventsManager::getInstance();

            if (_entitiesManager == nullptr || _entitiesManager->doesEntityExist("Floor") == false) {
                return;
            }

            if (events.isEventTriggered(Event::MOUSE_LEFT_PRESSED)) {
                const auto& floor = std::static_pointer_cast<Entities::Floor>(
                    _entitiesManager->getEntityById("Floor")
                );
                Vector2F mousePos = events.getWorldMousePos();
                Vector2F floorPos = floor->getPosition();
                Vector2F mapSize = floor->getMapSize();
                Vector2F tile = Vector2F(
                    static_cast<int>((mousePos.x - floorPos.x) / tileSize),
                    static_cast<int>((mousePos.y - floorPos.y) / tileSize)
                );
                if (mousePos.x >= floorPos.x && mousePos.x <= floorPos.x + mapSize.x &&
                    mousePos.y >= floorPos.y && mousePos.y <= floorPos.y + mapSize.y) {
                    if (_selectedTile == tile && _isTileSelected == true) {
                        _isTileSelected = false;
                        removeSelectedSprite();
                    } else {
                        _isTileSelected = true;
                        _selectedTile = tile;
                        removeSelectedSprite();
                        createSelectedSprite();
                    }
                }
            }
            if (_isTileSelected == true) {
                updateInfosSprite();
            }
        }

        void HUD::updateInfosSprite()
        {
        }

        void HUD::removeSelectedSprite()
        {
            _components.erase(
                std::remove_if(
                    _components.begin(),
                    _components.end(),
                    [this](const std::shared_ptr<GUI::Components::IComponent>& component) {
                        if (auto spriteComponent = std::dynamic_pointer_cast<GUI::Components::Sprite>(component)) {
                            auto entityId = spriteComponent->getId();
                            return entityId == selectedTileSpriteId || entityId == tileInfoSpriteId;
                        }
                        return false;
                    }
                ),
                _components.end()
            );
        }

        void HUD::createSelectedSprite()
        {
            EventsManager &em = EventsManager::getInstance();

            _components.push_back(std::make_shared<GUI::Components::Sprite>(
                selectedTileSpriteId,
                _txSelectedTile,
                selectedLayer,
                Vector2F(
                    _selectedTile.x * tileSize,
                    _selectedTile.y * tileSize
                ),
                tileSize,
                tileSize,
                Components::CompType::SPRITE
            ));
            _components.push_back(std::make_shared<GUI::Components::Sprite>(
                tileInfoSpriteId,
                _txTileInfos,
                tileInfosLayer,
                Vector2F(
                    margin,
                    margin
                ),
                infoWidth,
                infoHeight,
                Components::CompType::HUDSPRITE
            ));
        }

        void HUD::initTextures()
        {
            if (_txSelectedTile.loadFromFile(selectedSpritePath) == false) {
                throw EntityException("Error: could not load selected texture");
            }
            if (_txTileInfos.loadFromFile(tileInfoSpritePath) == false) {
                throw EntityException("Error: could not load tile infos texture");
            }
        }
    }
}
