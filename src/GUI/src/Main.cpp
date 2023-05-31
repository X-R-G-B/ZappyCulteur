/*
** EPITECH PROJECT, 2023
** zappy gui
** File description:
** main
*/

#include "SFML.hpp"
#include "EntitiesManager.hpp"
#include "Trantorian.hpp"
#include "Floor.hpp"

int main(void)
{
    GUI::SFML displayModule(
        nullptr,
        "Zappy bzz bzz",
        1920,
        1080,
        165,
        GUI::WINDOW_MODE::BORDERLESS
    );

    GUI::Entities::EntitiesManager entitiesManager;
    GUI::Entities::Trantorian trantorian("1", "team1", GUI::Vector2F(100, 100));
    GUI::Entities::Trantorian trantorian2("2", "team2", GUI::Vector2F(250, 200));
    GUI::Entities::Floor floor("1", GUI::Vector2F(0, 0), 20, 20);
    entitiesManager.addEntity(std::make_shared<GUI::Entities::Trantorian>(trantorian));
    entitiesManager.addEntity(std::make_shared<GUI::Entities::Trantorian>(trantorian2));
    entitiesManager.addEntity(std::make_shared<GUI::Entities::Floor>(floor));

    while (displayModule.isOpen()) {
        displayModule.handleEvents();
        entitiesManager.update();
        displayModule.update(entitiesManager);
    }
    return 0;
}
