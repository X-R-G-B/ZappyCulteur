/*
** EPITECH PROJECT, 2023
** proto
** File description:
** main
*/

#include <SFML/Graphics.hpp>
#include <iostream>
#include "NetworkManager.hpp"

//-------------------------------------------------------------//
//  TEST THE NETWORK MANAGER                                   //
//                                                             //
//  - Network connexion / reconnexion if needed                //
//  - With a server, send up, down, left, right                //
//  - Move cube with ZQSD to se if the network is not blocking //
//  - You can press space to send a message to the server      //
//  - You can press R to reconnect to the server               //
//-------------------------------------------------------------//

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Network Tests");
    window.setFramerateLimit(60);

    sf::RectangleShape cube(sf::Vector2f(50, 50));
    cube.setPosition(400, 300);
    cube.setFillColor(sf::Color::Red);
    
    float velocity = 300;
    float x = 400, y = 300;

    sf::Clock clock;

    Zappy::NetworkManager networkManager("localhost", "9999");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        try {
            networkManager.update();
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
        }

        float deltaTime = clock.restart().asSeconds();

        // CUBE MOVEMENTS
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
            y -= velocity * deltaTime;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            y += velocity * deltaTime;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
            x -= velocity * deltaTime;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            x += velocity * deltaTime;
        }

        // WINDOW EVENT

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window.close();
        }

        // NETWORK EVENTS

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            networkManager.sendToServer("testEnvoi\n");
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) &&
            networkManager.isConnected() == false) {
            networkManager.reconnectToServer();
        }

        for (const auto &response : networkManager.getServerMessages()) {
            if (response == "down") {
                y = 500;
            } else if (response == "up") {
                y = 50;
            } else if (response == "left") {
                x = 50;
            } else if (response == "right") {
                x = 720;
            } else {
                std::cout << "[" << response << "]" << std::endl;
            }
        }

        // DRAW AND DISPLAY

        cube.setPosition(x, y);
        window.clear();
        window.draw(cube);
        window.display();
    }
    return 0;
}
