/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** ADisplayModule
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "IDisplayModule.hpp"

namespace GUI {
    class ADisplayModule : public IDisplayModule {
        public:
            virtual bool isOpen() final;
            virtual unsigned int getWidth() final;
            virtual unsigned int getHeigth() final;
            virtual void setWidth(unsigned int width) final;
            virtual void setHeight(unsigned int height) final;
            virtual std::string getWindowTitle() final;
            virtual void setWindowTitle(std::string windowTitle) final;
            virtual unsigned int getFramerateLimit() final;
            virtual void setFramerateLimit(
            unsigned int framerateLimit) override;
            virtual void setWindowMode(WINDOW_MODE windowMode) final;

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
} // namespace GUI
