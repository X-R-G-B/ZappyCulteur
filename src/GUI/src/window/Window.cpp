/*
** EPITECH PROJECT, 2023
** zappy server
** File description:
** main
*/

#include "Window.hpp"

namespace GUI
{
    Window::Window(unsigned int width, unsigned int height, std::string title) :
        _windowSize(width, height),
        _windowTitle(title)
    {}

    Window::~Window()
    {
        if (_window.isOpen())
        {
            _window.close();
        }
    }

    void Window::createWindow()
    {
        _window.create(sf::VideoMode(_windowSize.x, _windowSize.y), _windowTitle);
        _window.setFramerateLimit(120);
    }

    void Window::displayWindow()
    {
        _window.display();
    }

    void Window::clearWindow()
    {
        _window.clear();
    }

    bool Window::isOpen() const
    {
        return _window.isOpen();
    }

    void Window::runEvents()
    {
        while (_window.pollEvent(_event))
        {
            if (_event.type == sf::Event::Closed)
            {
                _window.close();
            }
        }
    }
}
