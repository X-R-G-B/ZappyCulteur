/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** startMenu
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <chrono>
#include <memory>
#include <stdexcept>
#include "AEntity.hpp"
#include "EntitiesManager.hpp"

namespace GUI {
    namespace Entities {

        class startMenu : public AEntity {
            public:
                startMenu();
                ~startMenu() = default;
                void update(double deltaTime) final;
                const std::string &getIP() const;
                const std::string &getPort() const;
                bool isGameStarted() const;
            private:
                void initComponents();
                bool _isGameStarted;
                sf::Texture _backgroundTexture;
        };
    } // namespace Entities
} // namespace GUI
