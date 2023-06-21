/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** startMenu
*/

#include "startMenu.hpp"
#include "Components/Sprite.hpp"
#include "EventsManager.hpp"
#include "InputField.hpp"

static const std::string ID = "startMenu";
static const std::string MENU_BG_PATH = "src/GUI/assets/UI/menu.png";
static const std::string MENU_BG_ID = "menuBGSprite";
static const GUI::Vector2F MENU_POSITION = {0, 0};
static const GUI::Vector2F MENU_ROTATION = {0, 0};
static const GUI::Vector2F MENU_SCALE = {1, 1};
static const std::string IP_INPUT_ID = "ipInputField";
static const std::string PORT_INPUT_ID = "portInputField";
static const GUI::Vector2F IP_INPUT_POSITION = {1440, 200};
static const GUI::Vector2F PORT_INPUT_POSITION = {1440, 300};
static const unsigned int INPUT_SIZE = 20;
static const unsigned int LAYER_BACKGROUND = 0;
static const unsigned int BG_WITH = 1920;
static const unsigned int BG_HEIGHT = 1080;
static const std::string IP_INPUT_PLACEHOLDER = "Enter IP";
static const std::string PORT_INPUT_PLACEHOLDER = "Enter Port";
static const std::string menuMusicId = "menuMusic";
static const std::string menuMusicPath = "src/GUI/assets/musics/menu.ogg";

namespace GUI {
    namespace Entities {

        startMenu::startMenu()
            : AEntity(ID, MENU_POSITION, MENU_ROTATION, MENU_SCALE,
            EntityType::HUD, EntityOrientation::UP),
            _isGameStarted(false)
        {
            _entityCompType.push_back(Components::CompType::TEXT);
            _entityCompType.push_back(Components::CompType::INPUTFIELD);
            _entityCompType.push_back(Components::CompType::SPRITE);
            _entityCompType.push_back(Components::CompType::HUDSPRITE);
            _entityCompType.push_back(Components::CompType::MUSIC);
            initComponents();
        }

        void startMenu::update(double)
        {
        }

        void startMenu::initMusic()
        {
            _components.push_back(std::make_shared<GUI::Components::Music>(
            menuMusicId, menuMusicPath, true, true));
        }

        void startMenu::initComponents()
        {
            initMusic();
            _backgroundTexture.loadFromFile(MENU_BG_PATH);
            _components.push_back(std::make_shared<Components::Sprite>(
                MENU_BG_ID,
                _backgroundTexture,
                LAYER_BACKGROUND,
                MENU_POSITION,
                BG_WITH,
                BG_HEIGHT,
                Components::CompType::HUDSPRITE
            ));
            _components.push_back(std::make_shared<Components::InputField>(
                IP_INPUT_ID,
                IP_INPUT_PLACEHOLDER,
                IP_INPUT_POSITION,
                INPUT_SIZE
            ));
            _components.push_back(std::make_shared<Components::InputField>(
                PORT_INPUT_ID,
                PORT_INPUT_PLACEHOLDER,
                PORT_INPUT_POSITION,
                INPUT_SIZE
            ));
        }

        const std::string &startMenu::getIP() const
        {
            return "";
        }

        const std::string &startMenu::getPort() const
        {
            return "";
        }

        bool startMenu::isGameStarted() const
        {
            return _isGameStarted;
        }

    } // namespace Entities
} // namespace GUI
