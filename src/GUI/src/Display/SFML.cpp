/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** SFML
*/

#include <algorithm>
#include <unordered_map>
#include <iostream>
#include "CompQuery.hpp"
#include "SFML.hpp"
#include "Floor.hpp"
#include "IEntity.hpp"
#include "Music.hpp"
#include "Sprite.hpp"
#include "InputField.hpp"
#include "Button.hpp"

static const std::unordered_map<sf::Keyboard::Key, GUI::Event>
_keyboardMappings = {{sf::Keyboard::Num1, GUI::Event::KEYBOARD_1_PRESSED},
{sf::Keyboard::Num2, GUI::Event::KEYBOARD_2_PRESSED},
{sf::Keyboard::Num3, GUI::Event::KEYBOARD_3_PRESSED},
{sf::Keyboard::Num4, GUI::Event::KEYBOARD_4_PRESSED},
{sf::Keyboard::Num5, GUI::Event::KEYBOARD_5_PRESSED},
{sf::Keyboard::Num6, GUI::Event::KEYBOARD_6_PRESSED},
{sf::Keyboard::Num7, GUI::Event::KEYBOARD_7_PRESSED},
{sf::Keyboard::Num8, GUI::Event::KEYBOARD_8_PRESSED},
{sf::Keyboard::Num9, GUI::Event::KEYBOARD_9_PRESSED},
{sf::Keyboard::Num0, GUI::Event::KEYBOARD_0_PRESSED},
{sf::Keyboard::A, GUI::Event::KEYBOARD_A_PRESSED},
{sf::Keyboard::B, GUI::Event::KEYBOARD_B_PRESSED},
{sf::Keyboard::C, GUI::Event::KEYBOARD_C_PRESSED},
{sf::Keyboard::D, GUI::Event::KEYBOARD_D_PRESSED},
{sf::Keyboard::E, GUI::Event::KEYBOARD_E_PRESSED},
{sf::Keyboard::F, GUI::Event::KEYBOARD_F_PRESSED},
{sf::Keyboard::G, GUI::Event::KEYBOARD_G_PRESSED},
{sf::Keyboard::H, GUI::Event::KEYBOARD_H_PRESSED},
{sf::Keyboard::I, GUI::Event::KEYBOARD_I_PRESSED},
{sf::Keyboard::J, GUI::Event::KEYBOARD_J_PRESSED},
{sf::Keyboard::K, GUI::Event::KEYBOARD_K_PRESSED},
{sf::Keyboard::L, GUI::Event::KEYBOARD_L_PRESSED},
{sf::Keyboard::M, GUI::Event::KEYBOARD_M_PRESSED},
{sf::Keyboard::N, GUI::Event::KEYBOARD_N_PRESSED},
{sf::Keyboard::O, GUI::Event::KEYBOARD_O_PRESSED},
{sf::Keyboard::P, GUI::Event::KEYBOARD_P_PRESSED},
{sf::Keyboard::Q, GUI::Event::KEYBOARD_Q_PRESSED},
{sf::Keyboard::R, GUI::Event::KEYBOARD_R_PRESSED},
{sf::Keyboard::S, GUI::Event::KEYBOARD_S_PRESSED},
{sf::Keyboard::T, GUI::Event::KEYBOARD_T_PRESSED},
{sf::Keyboard::U, GUI::Event::KEYBOARD_U_PRESSED},
{sf::Keyboard::V, GUI::Event::KEYBOARD_V_PRESSED},
{sf::Keyboard::W, GUI::Event::KEYBOARD_W_PRESSED},
{sf::Keyboard::X, GUI::Event::KEYBOARD_X_PRESSED},
{sf::Keyboard::Y, GUI::Event::KEYBOARD_Y_PRESSED},
{sf::Keyboard::Z, GUI::Event::KEYBOARD_Z_PRESSED},
{sf::Keyboard::Up, GUI::Event::KEYBOARD_UP_PRESSED},
{sf::Keyboard::Down, GUI::Event::KEYBOARD_DOWN_PRESSED},
{sf::Keyboard::Left, GUI::Event::KEYBOARD_LEFT_PRESSED},
{sf::Keyboard::Right, GUI::Event::KEYBOARD_RIGHT_PRESSED},
{sf::Keyboard::Space, GUI::Event::KEYBOARD_SPACE_PRESSED},
{sf::Keyboard::Enter, GUI::Event::KEYBOARD_ENTER_PRESSED},
{sf::Keyboard::BackSpace, GUI::Event::KEYBOARD_BACKSPACE_PRESSED},
{sf::Keyboard::Tab, GUI::Event::KEYBOARD_TAB_PRESSED},
{sf::Keyboard::Escape, GUI::Event::KEYBOARD_ESCAPE_PRESSED},
{sf::Keyboard::LShift, GUI::Event::KEYBOARD_SHIFT_PRESSED},
{sf::Keyboard::LControl, GUI::Event::KEYBOARD_CTRL_PRESSED},
{sf::Keyboard::LAlt, GUI::Event::KEYBOARD_ALT_PRESSED}};

namespace GUI {
    SFML::SFML(std::shared_ptr<Entities::EntitiesManager> entityManager,
    std::string windowTitle, unsigned int width, unsigned int height,
    unsigned int framerateLimit, WINDOW_MODE windowMode)
        : _entityManager(entityManager), _camZoom(CAM_ZOOM_DEFAULT)
    {
        _windowTitle = windowTitle;
        _width = width;
        _height = height;
        _framerateLimit = framerateLimit;
        _windowMode = windowMode;
        setWindowStyle();
        createWindow();
    }

    SFML::~SFML()
    {
        closeWindow();
    }

    WINDOW_MODE SFML::getWindowMode()
    {
        return _windowMode;
    }

    void SFML::createWindow()
    {
        _window.create(sf::VideoMode(_width, _height), _windowTitle, _winStyle);
        _window.setFramerateLimit(_framerateLimit);
        _isOpen = true;
        _view.setSize(static_cast<float>(_width), static_cast<float>(_height));
        _view.setCenter(
        static_cast<float>(_width) / 2, static_cast<float>(_height) / 2);
        _HUDview.setSize(
        static_cast<float>(_width), static_cast<float>(_height));
        _HUDview.setCenter(
        static_cast<float>(_width) / 2, static_cast<float>(_height) / 2);
    }

    void SFML::clear()
    {
        _window.clear(sf::Color::Black);
        _window.setView(_view);
    }

    void SFML::closeWindow()
    {
        if (_isOpen == true) {
            _window.close();
        }
        _isOpen = false;
    }

    void SFML::setWindowStyle()
    {
        if (_windowMode == WINDOW_MODE::FULLSCREEN) {
            _winStyle = sf::Style::Fullscreen;
        } else if (_windowMode == WINDOW_MODE::BORDERLESS) {
            _winStyle = sf::Style::None;
        } else {
            _winStyle = sf::Style::Titlebar | sf::Style::Close;
        }
    }

    void SFML::update(double deltaTime)
    {
        lookForCloseEvent();
        moveCamera(deltaTime);
        zoomCamera();
        clear();
        playMusics();
        drawSprites();
        drawTexts();
        _window.setView(_HUDview);
        drawHUD();
        _window.setView(_view);
        _window.display();
    }

    void SFML::playMusics()
    {
        auto musics =
        _entityManager->getComponentsByType(Components::CompType::MUSIC);

        for (const auto &music : *musics) {
            auto musicPtr =
            std::static_pointer_cast<GUI::Components::Music>(music);
            if (musicPtr == nullptr) {
                continue;
            }
            if (musicPtr->getNeedToPlay() == true) {
                musicPtr->play();
                musicPtr->setNeedToPlay(false);
            }
            if (musicPtr->getNeedToStop() == true) {
                musicPtr->stop();
                musicPtr->setNeedToStop(false);
            }
        }
    }

    void SFML::drawHUD()
    {
        auto sprites =
        _entityManager->getComponentsByType(Components::CompType::HUDSPRITE);
        auto texts =
        _entityManager->getComponentsByType(Components::CompType::HUDTEXT);
        auto inputFields =
        _entityManager->getComponentsByType(Components::CompType::INPUTFIELD);
        auto buttons =
        _entityManager->getComponentsByType(Components::CompType::BUTTON);

        for (const auto &sprite : *sprites) {
            auto spritePtr =
            std::static_pointer_cast<GUI::Components::Sprite>(sprite);
            if (spritePtr == nullptr) {
                continue;
            }
            _window.draw(spritePtr->getSprite());
        }
        for (const auto &text : *texts) {
            auto textPtr =
            std::static_pointer_cast<GUI::Components::Text>(text);
            if (textPtr == nullptr) {
                continue;
            }
            _window.draw(textPtr->getText());
        }
        for (const auto &inputField : *inputFields) {
            auto inputFieldPtr =
            std::static_pointer_cast<GUI::Components::InputField>(inputField);
            if (inputFieldPtr == nullptr) {
                continue;
            }
            _window.draw(inputFieldPtr->getSprite());
            _window.draw(inputFieldPtr->getText());
        }
        for (const auto &button : *buttons) {
            auto buttonPtr =
            std::static_pointer_cast<GUI::Components::Button>(button);
            if (buttonPtr == nullptr) {
                continue;
            }
            _window.draw(buttonPtr->getSprite());
            _window.draw(buttonPtr->getText());
        }
    }

    void SFML::drawSprites()
    {
        auto sprites =
        _entityManager->getComponentsByType(Components::CompType::SPRITE);
        _compQuery.sortSpritesByLayer(sprites);

        for (const auto &sprite : *sprites) {
            auto spritePtr =
            std::static_pointer_cast<GUI::Components::Sprite>(sprite);
            if (spritePtr == nullptr) {
                continue;
            }
            _window.draw(spritePtr->getSprite());
        }
    }

    void SFML::drawTexts()
    {
        auto texts =
        _entityManager->getComponentsByType(Components::CompType::TEXT);

        for (const auto &text : *texts) {
            auto textPtr =
            std::static_pointer_cast<GUI::Components::Text>(text);
            if (textPtr == nullptr) {
                continue;
            }
            _window.draw(textPtr->getText());
        }
    }

    void SFML::handleEvents(double)
    {
        EventsManager &eventsManager = EventsManager::getInstance();

        eventsManager.clearEvents();
        while (_window.pollEvent(_event)) {
            if (_event.type == sf::Event::Closed) {
                eventsManager.addEvent(GUI::Event::WINDOW_CLOSED);
            }
            handleMouseEvents(eventsManager);
            handleKeyboardEvents(eventsManager);
        }
    }

    void SFML::handleMousePosEvents(EventsManager &eventsManager)
    {
        if (_event.type == sf::Event::MouseMoved) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(_window);
            Vector2F mousePosF = {
            static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)};
            eventsManager.addMousePos(mousePosF);
        }
        sf::Vector2i mousePos = sf::Mouse::getPosition(_window);
        sf::Vector2f worldMousePos = _window.mapPixelToCoords(mousePos);
        Vector2F worldMousePosF = {worldMousePos.x, worldMousePos.y};
        eventsManager.addWorldMousePos(worldMousePosF);
    }

    void SFML::handleMouseEvents(EventsManager &eventsManager)
    {
        handleMousePosEvents(eventsManager);
        if (_event.type == sf::Event::MouseWheelScrolled) {
            if (_event.mouseWheelScroll.delta > 0) {
                eventsManager.addEvent(GUI::Event::MOUSE_WHEEL_UP);
            } else if (_event.mouseWheelScroll.delta < 0) {
                eventsManager.addEvent(GUI::Event::MOUSE_WHEEL_DOWN);
            }
        }
        if (_event.type == sf::Event::MouseButtonPressed) {
            if (_event.mouseButton.button == sf::Mouse::Left) {
                eventsManager.addEvent(GUI::Event::MOUSE_LEFT_PRESSED);
            } else if (_event.mouseButton.button == sf::Mouse::Right) {
                eventsManager.addEvent(GUI::Event::MOUSE_RIGHT_PRESSED);
            }
        }
    }

    void SFML::handleKeyboardEvents(EventsManager &eventsManager)
    {
        for (auto &keyboardMapping : _keyboardMappings) {
            if (sf::Keyboard::isKeyPressed(keyboardMapping.first)) {
                eventsManager.addEvent(keyboardMapping.second);
            }
        }
        if (_event.type == sf::Event::TextEntered) {
            if (_event.text.unicode == '.') {
                eventsManager.addEvent(GUI::Event::KEYBOARD_DOT_PRESSED);
            }
        }
    }

    void SFML::switchWindowMode()
    {
        closeWindow();
        setWindowStyle();
        createWindow();
    }

    void SFML::lookForCloseEvent()
    {
        EventsManager &eventsManager = EventsManager::getInstance();

        if (eventsManager.isEventTriggered(GUI::Event::WINDOW_CLOSED) == true
        || eventsManager.isEventTriggered(GUI::Event::KEYBOARD_ESCAPE_PRESSED)== true
        || eventsManager.isEventTriggered(GUI::Event::QUIT_GAME) == true) {
            closeWindow();
        }
    }

    void SFML::zoomCamera()
    {
        EventsManager &eventsManager = EventsManager::getInstance();

        if (eventsManager.isEventTriggered(GUI::Event::MOUSE_WHEEL_UP)
        == true) {
            _view.zoom(_camZoom + CAM_ZOOM_SPEED);
        } else if (eventsManager.isEventTriggered(GUI::Event::MOUSE_WHEEL_DOWN)
        == true) {
            _view.zoom(_camZoom - CAM_ZOOM_SPEED);
        }
        _camZoom = CAM_ZOOM_DEFAULT;
    }

    void SFML::moveCamera(double deltaTime)
    {
        Vector2F mapSize = {0, 0};
        sf::Vector2f viewSize = {0, 0};
        sf::Vector2f viewCenter = {0, 0};
        float offset = static_cast<float>(CAM_SPEED * deltaTime);

        if (_entityManager->doesEntityExist("Floor") == false) {
            return;
        }
        try {
            auto floor = _entityManager->getEntityById("Floor");
            auto floorPtr =
            std::static_pointer_cast<GUI::Entities::Floor>(floor);
            mapSize = floorPtr->getMapSize();
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
            return;
        }
        viewCenter = _view.getCenter();
        viewSize = _view.getSize();
        applyCamMovements(viewCenter, viewSize, mapSize, offset);
    }

    void SFML::applyCamMovements(sf::Vector2f viewCenter, sf::Vector2f viewSize,
    Vector2F mapSize, float offset)
    {
        EventsManager &eventsManager = EventsManager::getInstance();

        if (eventsManager.isEventTriggered(GUI::Event::KEYBOARD_Z_PRESSED)
        == true
        && viewCenter.y - viewSize.y / 2 > 0) {
            _view.move(0, -offset);
        } else if (eventsManager.isEventTriggered(
                   GUI::Event::KEYBOARD_S_PRESSED)
        == true
        && viewCenter.y + viewSize.y / 2 < mapSize.y) {
            _view.move(0, offset);
        }
        if (eventsManager.isEventTriggered(GUI::Event::KEYBOARD_Q_PRESSED)
        == true
        && viewCenter.x - viewSize.x / 2 > 0) {
            _view.move(-offset, 0);
        } else if (eventsManager.isEventTriggered(
                   GUI::Event::KEYBOARD_D_PRESSED)
        == true
        && viewCenter.x + viewSize.x / 2 < mapSize.x) {
            _view.move(offset, 0);
        }
    }
} // namespace GUI
