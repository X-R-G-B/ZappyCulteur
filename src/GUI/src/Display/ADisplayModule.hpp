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
            bool isOpen() final;
            unsigned int getWidth() final;
            unsigned int getHeigth() final;
            void setWidth(unsigned int width) final;
            void setHeight(unsigned int height) final;
            std::string getWindowTitle() final;
            void setWindowTitle(std::string windowTitle) final;
            unsigned int getFramerateLimit() final;
            void setWindowMode(WINDOW_MODE windowMode) final;
            WINDOW_MODE getWindowMode() final;
        protected:
            virtual void clear() = 0;
            virtual void closeWindow() = 0;
            virtual void createWindow() = 0;
            virtual void switchWindowMode() = 0;
            bool _isOpen;
            unsigned int _width;
            unsigned int _height;
            unsigned int _framerateLimit;
            std::string _windowTitle;
            WINDOW_MODE _windowMode;
    };
}
