/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** ADisplayModule
*/

#pragma once

#include <memory>
#include <SFML/Graphics.hpp>

#include "IDisplayModule.hpp"

namespace GUI {
    class ADisplayModule : public IDisplayModule {
        public:
            bool isOpen() override;
            unsigned int getWidth() override;
            unsigned int getHeigth() override;
            void setWidth(unsigned int width) override;
            void setHeight(unsigned int height) override;
            std::string getWindowTitle() override;
            void setWindowTitle(std::string windowTitle) override;
            unsigned int getFramerateLimit() override;
            void setFramerateLimit(unsigned int framerateLimit) override;
            void setWindowMode(WINDOW_MODE windowMode) override;
        protected:
            virtual void clear() = 0;
            virtual void closeWindow() = 0;
            virtual void createWindow() = 0;
            virtual void switchWindowMode() = 0;
            bool _isOpen;
            unsigned int _width;
            unsigned int _height;
            unsigned int _framerateLimit;
            std::string _windowTitle = "ZappyCulteur";
            WINDOW_MODE _windowMode = WINDOW_MODE::FULLSCREEN;
    };
}
