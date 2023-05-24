/*
** EPITECH PROJECT, 2023
** zappy server
** File description:
** main
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

namespace GUI
{
    class Window
    {
        public:
            Window(
                unsigned int width = 800U,
                unsigned int height = 600U,
                std::string title = "Zappy"
            );
            ~Window();
            void createWindow();
            void displayWindow();
            void runEvents();
            void clearWindow();
            bool isOpen() const;
        
        private:
            sf::RenderWindow _window;
            sf::Vector2u _windowSize;
            std::string _windowTitle;
            sf::Event _event;
    };
}
