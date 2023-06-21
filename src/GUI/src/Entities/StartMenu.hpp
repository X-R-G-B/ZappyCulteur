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
#include <string>
#include "AEntity.hpp"
#include "EntitiesManager.hpp"
#include "Music.hpp"
#include "Button.hpp"
#include "InputField.hpp"

namespace GUI {
    namespace Entities {

        class startMenu : public AEntity {
            public:
                startMenu();
                ~startMenu() = default;
                void update(double deltaTime) final;
                const std::string &getIP();
                const std::string &getPort();
                bool isGameStarted() const;
            private:
                void initComponents();
                void initInputFields();
                bool _isGameStarted;
                void initMusic();
                void cleanInputFields(std::string &str);
                std::string _ip;
                std::string _port;
                sf::Texture _backgroundTexture;
                std::shared_ptr<Components::InputField> _ipInputField;
                std::shared_ptr<Components::InputField> _portInputField;
        };
    } // namespace Entities
} // namespace GUI
