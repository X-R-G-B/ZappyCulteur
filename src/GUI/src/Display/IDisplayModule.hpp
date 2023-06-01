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
#include "EntitiesManager.hpp"

namespace GUI {
        enum class WINDOW_MODE {
            WINDOWED,
            FULLSCREEN,
            BORDERLESS
        };

    class IDisplayModule {
        public:
            ~IDisplayModule() = default;
            /**
             * @brief Clear, draw and display (sprites, sounds, etc...)
             * @param entitiesManger
             */
            virtual void update(Entities::EntitiesManager &entitiesManger) = 0;
            
            /**
             * @brief say if the window is open or not
             */
            virtual bool isOpen() = 0;

            /**
             * @brief handle events (keyboard, mouse, etc...)
             */
            virtual void handleEvents() = 0;

            /**
             * @brief set the framerate limit of the window
             * @param framerateLimit
             */
            virtual void setFramerateLimit(unsigned int framerateLimit) = 0;

            /**
             * @brief get the framerate limit of the window
             */
            virtual unsigned int getFramerateLimit() = 0;

            /**
             * @brief set the width of the window
             * @param width
             */
            virtual void setWidth(unsigned int width) = 0;

            /**
             * @brief set the height of the window
             * @param height
             */
            virtual void setHeight(unsigned int height) = 0;

            /**
             * @brief get the width of the window
             */
            virtual unsigned int getWidth() = 0;

            /**
             * @brief get the height of the window
             */
            virtual unsigned int getHeigth() = 0;

            /**
             * @brief set the title of the window
             * @param windowTitle
             */
            virtual void setWindowTitle(std::string windowTitle) = 0;

            /**
             * @brief get the title of the window
             */
            virtual std::string getWindowTitle() = 0;

            /**
             * @brief set the window mode
             * @param windowMode
             */
            virtual WINDOW_MODE getWindowMode() = 0;

            /**
             * @brief switch the window mode
             */
            virtual void setWindowMode(WINDOW_MODE windowMode) = 0;
    };
}
