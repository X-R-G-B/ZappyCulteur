/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** SFML
*/

#include <map>
#include "SFML.hpp"
#include "IEntity.hpp"
#include "Sprite.hpp"
#include "CompQuery.hpp"

namespace GUI {
    SFML::SFML(std::shared_ptr<GUI::EntityManager> entityManager,
        std::string windowTitle,
        unsigned int width,
        unsigned int height,
        unsigned int framerateLimit,
        WINDOW_MODE windowMode
    ) :
        _entityManager(entityManager)
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
    }

    void SFML::clear()
    {
        _window.clear(sf::Color::Black);
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
            _winStyle = sf::Style::Default;
        }
    }

    void SFML::update(Entities::EntitiesManager &entitiesManger)
    {
        clear();
        drawSprites(entitiesManger);
        _window.display();
    }

    void SFML::drawSprites(Entities::EntitiesManager &entitiesManger)
    {
        auto sprites = _compQuery.sortSpritesByLayer(entitiesManger.getComponentsByType(Components::CompType::SPRITE));

        for (auto &sprite : *sprites) {
            for (auto &spriteComponent : sprite.second) {
                auto spritePtr = std::static_pointer_cast<GUI::Components::Sprite>(spriteComponent);
                if (spritePtr == nullptr) {
                    continue;
                }
                _window.draw(spritePtr->getSprite());
            }
        }
    }

    void SFML::handleEvents()
    {
        while (_window.pollEvent(_event)) {
            if (_event.type == sf::Event::Closed ||
                (_event.type == sf::Event::KeyPressed &&
                _event.key.code == sf::Keyboard::Escape)) {
                closeWindow();
            }
        }
    }

    void SFML::switchWindowMode()
    {
        closeWindow();
        setWindowStyle();
        createWindow();
    }
}
