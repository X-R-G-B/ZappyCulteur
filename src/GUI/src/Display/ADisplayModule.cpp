/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** ADisplayModule
*/

#include "ADisplayModule.hpp"

namespace GUI {
    bool ADisplayModule::isOpen()
    {
        return _isOpen;
    }

    void ADisplayModule::setFramerateLimit(unsigned int framerateLimit)
    {
        _framerateLimit = framerateLimit;
    }

    unsigned int ADisplayModule::getFramerateLimit()
    {
        return _framerateLimit;
    }

    void ADisplayModule::setWidth(unsigned int width)
    {
        _width = width;
    }

    void ADisplayModule::setHeight(unsigned int height)
    {
        _height = height;
    }

    unsigned int ADisplayModule::getHeigth()
    {
        return _height;
    }

    unsigned int ADisplayModule::getWidth()
    {
        return _width;
    }

    void ADisplayModule::setWindowTitle(std::string windowTitle)
    {
        _windowTitle = windowTitle;
    }

    std::string ADisplayModule::getWindowTitle()
    {
        return _windowTitle;
    }

    void ADisplayModule::setWindowMode(WINDOW_MODE windowMode)
    {
        _windowMode = windowMode;
        switchWindowMode();
    }
} // namespace GUI
