/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** IDisplayModule
*/

#pragma once
#include <vector>
#include <memory>
#include "IEntity.hpp"

namespace GUI {
        enum class WINDOW_MODE {
            WINDOWED,
            FULLSCREEN,
            BORDERLESS
        };

    class IDisplayModule {
        public:
            ~IDisplayModule() = default;
            virtual void update(const std::vector<std::shared_ptr<GUI::Entities::IEntity>> &entities) = 0;
            virtual bool isOpen() = 0;
            virtual void handleEvents() = 0;
            virtual void setFramerateLimit(unsigned int framerateLimit) = 0;
            virtual unsigned int getFramerateLimit() = 0;
            virtual void setWidth(unsigned int width) = 0;
            virtual void setHeight(unsigned int height) = 0;
            virtual unsigned int getWidth() = 0;
            virtual unsigned int getHeigth() = 0;
            virtual void setWindowTitle(std::string windowTitle) = 0;
            virtual std::string getWindowTitle() = 0;
            virtual WINDOW_MODE getWindowMode() = 0;
            virtual void setWindowMode(WINDOW_MODE windowMode) = 0;
    };
}
