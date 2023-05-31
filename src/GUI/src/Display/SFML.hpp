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
#include "CompQuery.hpp"
#include "ADisplayModule.hpp"
#include "EntitiesManager.hpp"

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
            virtual void update(Entities::EntitiesManager &entitiesManger) final;
            virtual void handleEvents() final;
            WINDOW_MODE getWindowMode();
        private:
            void clear() final;
            void closeWindow()final;
            void drawSprites(Entities::EntitiesManager &entitiesManger);
            void createWindow() final;
            void setWindowStyle();
            void switchWindowMode() final;
            sf::Event _event;
            sf::Uint32 _winStyle;
            sf::RenderWindow _window;
            Components::CompQuery _compQuery;
            std::shared_ptr<GUI::EntityManager> _entityManager;
    };
}
