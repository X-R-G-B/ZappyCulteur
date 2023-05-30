/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** SFML
*/

#include "SFML.hpp"

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

    void SFML::setWindowStyle()
    {
        if (_windowMode == WINDOW_MODE::FULLSCREEN) {
            _winStyle = 8U;
        } else if (_windowMode == WINDOW_MODE::BORDERLESS) {
            _winStyle = 6U;
        } else {
            _winStyle = 7U;
        }
    }

    void SFML::setWindowMode(WINDOW_MODE windowMode)
    {
        _windowMode = windowMode;
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

    void SFML::update()
    {
        clear();
        //draw here
        _window.display();
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
}
