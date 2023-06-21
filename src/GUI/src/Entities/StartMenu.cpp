/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** startMenu
*/

#include "startMenu.hpp"
#include "Components/Sprite.hpp"
#include "EventsManager.hpp"

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
const std::string BTN_PLAY_ID = "startButton";
static const std::string BTN_PLAY_TEXT = "Start";
static const GUI::Vector2F BTN_PLAY_POSITION = {1425, 800};
static GUI::Event BTN_PLAY_EVENT = GUI::Event::START_GAME;
static const std::string BTN_QUIT_ID = "quitButton";
static const std::string BTN_QUIT_TEXT = "Quit Game";
static const GUI::Vector2F BTN_QUIT_POSITION = {1425, 900};
static const GUI::Event BTN_QUIT_EVENT = GUI::Event::QUIT_GAME;

namespace GUI {
    namespace Entities {

        startMenu::startMenu()
            : AEntity(ID, MENU_POSITION, MENU_ROTATION, MENU_SCALE,
            EntityType::HUD, EntityOrientation::UP),
            _isGameStarted(false),
            _ipInputField(nullptr),
            _portInputField(nullptr)
        {
            _entityCompType.push_back(Components::CompType::TEXT);
            _entityCompType.push_back(Components::CompType::INPUTFIELD);
            _entityCompType.push_back(Components::CompType::SPRITE);
            _entityCompType.push_back(Components::CompType::HUDSPRITE);
            _entityCompType.push_back(Components::CompType::MUSIC);
            _entityCompType.push_back(Components::CompType::BUTTON);
            initComponents();
        }

        void startMenu::update(double)
        {
            if (EventsManager::getInstance().isEventTriggered(BTN_PLAY_EVENT)) {
                _isGameStarted = true;
            }
        }

        void startMenu::initMusic()
        {
            _components.push_back(std::make_shared<GUI::Components::Music>(
            menuMusicId, menuMusicPath, true, true));
        }

        void startMenu::initComponents()
        {
            initMusic();
            initInputFields();
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
            _components.push_back(std::make_shared<Components::Button>(
                BTN_PLAY_ID,
                BTN_PLAY_TEXT,
                BTN_PLAY_POSITION,
                BTN_PLAY_EVENT
            ));
            _components.push_back(std::make_shared<Components::Button>(
                BTN_QUIT_ID,
                BTN_QUIT_TEXT,
                BTN_QUIT_POSITION,
                BTN_QUIT_EVENT
            ));
        }

        void startMenu::initInputFields()
        {
            _ipInputField = std::make_shared<Components::InputField>(
                IP_INPUT_ID,
                IP_INPUT_PLACEHOLDER,
                IP_INPUT_POSITION,
                INPUT_SIZE
            );
            _portInputField = std::make_shared<Components::InputField>(
                PORT_INPUT_ID,
                PORT_INPUT_PLACEHOLDER,
                PORT_INPUT_POSITION,
                INPUT_SIZE
            );
            _components.push_back(_ipInputField);
            _components.push_back(_portInputField);
        }

        void startMenu::cleanInputFields(std::string &str)
        {
            str.erase(std::remove_if(str.begin(), str.end(), [](char c) {
                return !(std::isdigit(c) || c == '.' || std::isalpha(c));
            }), str.end());
        }

        const std::string &startMenu::getIP()
        {
            if (_ipInputField != nullptr) {
                _ip = _ipInputField->getTextString();
                cleanInputFields(_ip);
            }
            return _ip;
        }

        const std::string &startMenu::getPort()
        {
            if (_portInputField != nullptr) {
                _port = _portInputField->getTextString();
                cleanInputFields(_port);
            }
            return _port;
        }

        bool startMenu::isGameStarted() const
        {
            return _isGameStarted;
        }

    } // namespace Entities
} // namespace GUI
