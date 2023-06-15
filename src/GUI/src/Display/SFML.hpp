/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** SFML
*/

#pragma once

#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "CompQuery.hpp"
#include "ADisplayModule.hpp"
#include "EntitiesManager.hpp"

namespace GUI {
    class SFML : public ADisplayModule {
        public:
            SFML(std::shared_ptr<GUI::Entities::EntitiesManager> entityManager,
                std::string windowTitle = "ZappyCulteur",
                unsigned int width = 1920U,
                unsigned int height = 1080U,
                unsigned int framerateLimit = 60U,
                WINDOW_MODE windowMode = WINDOW_MODE::FULLSCREEN
            );
            ~SFML();
            virtual void update(double deltaTime) final;
            virtual void handleEvents(double deltaTime) final;
            WINDOW_MODE getWindowMode();
        private:
            static constexpr float CAM_SPEED = 1000.0f;
            static constexpr float CAM_ZOOM_DEFAULT = 1.0f;
            static constexpr float CAM_ZOOM_SPEED = 0.1f;
            void clear() final;
            void closeWindow()final;
            void drawSprites();
            void drawTexts();
            void createWindow() final;
            void setWindowStyle();
            void switchWindowMode() final;
            void moveCamera(double deltaTime);
            void zoomCamera();
            void lookForCloseEvent();
            void applyCamMovements(
                sf::Vector2f viewCenter,
                sf::Vector2f viewSize,
                Vector2F mapSize,
                float offset
            );
            sf::Event _event;
            sf::Uint32 _winStyle;
            sf::RenderWindow _window;
            Components::CompQuery _compQuery;
            std::shared_ptr<Entities::EntitiesManager> _entityManager;
            sf::View _view;
            float _camZoom;
    };
}
