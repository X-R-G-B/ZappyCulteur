/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** SFML
*/

#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "ADisplayModule.hpp"

namespace GUI {
    class EntityManager;
}

namespace GUI {
    class SFML : public ADisplayModule {
        public:
            SFML(std::shared_ptr<GUI::EntityManager> entityManager,
                std::string windowTitle = "ZappyCulteur",
                unsigned int width = 1920U,
                unsigned int height = 1080U,
                unsigned int framerateLimit = 144U,
                WINDOW_MODE windowMode = WINDOW_MODE::FULLSCREEN
            );
            ~SFML();
            void update() override;
            void handleEvents() override;
            WINDOW_MODE getWindowMode();
        private:
            void clear() override;
            void closeWindow()override;
            void createWindow() override;
            void setWindowStyle();
            void switchWindowMode() override;
            sf::Event _event;
            sf::Uint32 _winStyle;
            sf::RenderWindow _window;
            std::shared_ptr<GUI::EntityManager> _entityManager;
    };
}
