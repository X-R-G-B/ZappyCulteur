/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** HUD
*/

#include "Components/Sprite.hpp"
#include "HUD.hpp"
#include "Color.hpp"
#include "Floor.hpp"
#include "EventsManager.hpp"
#include "Floor.hpp"
#include <iostream>

static constexpr float margin = 20.0f;
static constexpr float tileSize = 92.0f;
static const GUI::Vector2F HUD_SCALE = {1, 1};
static const GUI::Vector2F HUD_ROTATION = {0, 0};
static const GUI::Vector2F HUD_POSITION = {0, 0};

////////////////////// RESSOURCES COUNTER SPRITES //////////////////////
//                                                                    //
//                                                                    //
//                                                                    //
//                                                                    //
////////////////////////////////////////////////////////////////////////

static const std::size_t selectedLayer = 150;
static const std::size_t tileInfosLayer = 200;
static constexpr unsigned int infoWidth = 212;
static constexpr unsigned int infoHeight = 288;

static const std::string selectedSpritePath = "src/GUI/assets/environment/selected.png";
static const std::string tileInfoSpritePath = "src/GUI/assets/UI/tileInfos.png";
static const std::string tileInfoSpriteId = "tileInfoSprite";
static const std::string selectedTileSpriteId = "selectedTileSprite";

////////////////////// RESSOURCES COUNTER TEXTES ///////////////////////
//                                                                    //
//                                                                    //
//                                                                    //
//                                                                    //
////////////////////////////////////////////////////////////////////////

static constexpr float marginBetweenTexts = infoHeight / 7.2;

static const std::string foodTxtId = "foodTxt";
static const std::string linemateTxtId = "linemateTxt";
static const std::string deraumereTxtId = "deraumereTxt";
static const std::string siburTxtId = "siburTxt";
static const std::string mendianeTxtId = "mendianeTxt";
static const std::string phirasTxtId = "phirasTxt";
static const std::string thystameTxtId = "thystameTxt";

static const std::unordered_map<GUI::Entities::RessourcesType, GUI::Vector2F> ressourcesTextsPos = {
    {GUI::Entities::RessourcesType::FOOD, {infoWidth - 5, margin + 7}},
    {GUI::Entities::RessourcesType::LINEMATE, {infoWidth - 5, margin + marginBetweenTexts + 7}},
    {GUI::Entities::RessourcesType::DERAUMERE, {infoWidth - 5, margin + marginBetweenTexts * 2 + 7}},
    {GUI::Entities::RessourcesType::SIBUR, {infoWidth - 5, margin + marginBetweenTexts * 3 + 7}},
    {GUI::Entities::RessourcesType::MENDIANE, {infoWidth - 5, margin + marginBetweenTexts * 4 + 7}},
    {GUI::Entities::RessourcesType::PHIRAS, {infoWidth - 5, margin + marginBetweenTexts * 5 + 7}},
    {GUI::Entities::RessourcesType::THYSTAME, {infoWidth - 5, margin + marginBetweenTexts * 6 + 7}}
};

static const std::unordered_map<std::string, GUI::Entities::RessourcesType> idToRessourcesTypeMap = {
    { foodTxtId, GUI::Entities::RessourcesType::FOOD },
    { linemateTxtId, GUI::Entities::RessourcesType::LINEMATE },
    { deraumereTxtId, GUI::Entities::RessourcesType::DERAUMERE },
    { siburTxtId, GUI::Entities::RessourcesType::SIBUR },
    { mendianeTxtId, GUI::Entities::RessourcesType::MENDIANE },
    { phirasTxtId, GUI::Entities::RessourcesType::PHIRAS },
    { thystameTxtId, GUI::Entities::RessourcesType::THYSTAME }
};

//////////////////// END OF STATIC VARIABLES ///////////////////////////
//                                                                    //
//                                                                    //
//                                                                    //
//                                                                    //
////////////////////////////////////////////////////////////////////////

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
            _entityCompType.push_back(Components::CompType::HUDTEXT);
            _entityCompType.push_back(Components::CompType::SPRITE);
            initTextures();
        }

        void HUD::update(double)
        {
            if (_entitiesManager == nullptr || _entitiesManager->doesEntityExist("Floor") == false) {
                return;
            }
            updateSelectedTile();
            if (_isTileSelected == true) {
                updateCounterBox();
            }
        }

        void HUD::updateCounterBox()
        {
            const auto& texts = _entitiesManager->getComponentsByType(Components::CompType::HUDTEXT);

            for (const auto& text : *texts) {
                auto textComponent = std::dynamic_pointer_cast<GUI::Components::Text>(text);
                if (textComponent == nullptr) {
                    continue;
                }
                if (auto textComponent = std::dynamic_pointer_cast<GUI::Components::Text>(text)) {
                    std::string id = textComponent->getId();
                    try {
                        auto ressourceType = idToRessourcesTypeMap.at(id);
                        auto amount = getRessourceAmount(ressourceType, _selectedTile);
                        textComponent->setText(std::to_string(amount));
                    } catch (const std::out_of_range& e) {
                        continue;
                    }
                }
            }
        }

        void HUD::updateSelectedTile()
        {
            EventsManager &events = EventsManager::getInstance();

            if (events.isEventTriggered(Event::MOUSE_LEFT_PRESSED) == false) {
                return;
            }
            const auto& floor = std::static_pointer_cast<Entities::Floor>(
                _entitiesManager->getEntityById("Floor")
            );
            Vector2F mousePos = events.getWorldMousePos();
            Vector2F floorPos = floor->getPosition();
            Vector2F tile = Vector2F(
                std::floor((mousePos.x - floorPos.x) / tileSize),
                std::floor((mousePos.y - floorPos.y) / tileSize)
            );
            if (mousePos.x >= floorPos.x && mousePos.x <= floorPos.x + floor->getMapSize().x &&
                mousePos.y >= floorPos.y && mousePos.y <= floorPos.y + floor->getMapSize().y) {
                if (_selectedTile == tile && _isTileSelected == true) {
                    _isTileSelected = false;
                    removeSelectedSprite();
                    removeInfoTexts();
                } else {
                    _isTileSelected = true;
                    _selectedTile = tile;
                    removeSelectedSprite();
                    removeInfoTexts();
                    createSelectedSprite();
                }
            }
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

        void HUD::removeInfoTexts()
        {
            _components.erase(
                std::remove_if(
                    _components.begin(),
                    _components.end(),
                    [this](const std::shared_ptr<GUI::Components::IComponent>& component) {
                        if (auto textComponent = std::dynamic_pointer_cast<GUI::Components::Text>(component)) {
                            auto entityId = textComponent->getId();
                            return idToRessourcesTypeMap.find(entityId) != idToRessourcesTypeMap.end();
                        }
                        return false;
                    }
                ),
                _components.end()
            );
        }

        void HUD::createSelectedSprite()
        {
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
            for (const auto& [id, type] : idToRessourcesTypeMap) {
                createQuantityText(id, type, ressourcesTextsPos.at(type));
            }
        }

        void HUD::createQuantityText(const std::string &id, RessourcesType ressourceType, Vector2F pos)
        {
            static const std::string defaultText = "0";
            static constexpr std::size_t fontSize = 20;
            static const Color color = Color(255, 255, 255, 255);

            _components.push_back(std::make_shared<GUI::Components::Text>(
                id,
                defaultText,
                pos,
                color,
                fontSize,
                Components::CompType::HUDTEXT
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

        unsigned int HUD::getRessourceAmount(GUI::Entities::RessourcesType type, Vector2F tile)
        {
            if (_entitiesManager == nullptr || _entitiesManager->doesEntityExist("Floor") == false) {
                return (0);
            }
            const auto& floor = std::static_pointer_cast<Entities::Floor>(
                _entitiesManager->getEntityById("Floor")
            );
            return (floor->getRessourceAmount(tile, type));
        }
    }
}
