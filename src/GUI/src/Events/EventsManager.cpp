/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** Events
*/

#include "EventsManager.hpp"

GUI::EventsManager::EventsManager() :
    _mousePos({0, 0}),
    _worldMousePos({0, 0})
{}

void GUI::EventsManager::addEvent(GUI::Event event)
{
    _eventsList.push_back(event);
}

void GUI::EventsManager::addMousePos(Vector2F mousePos)
{
    _mousePos = mousePos;
}

void GUI::EventsManager::clearEvents()
{
    _eventsList.clear();
}

const GUI::Vector2F &GUI::EventsManager::getMousePos()
{
    return _mousePos;
}

bool GUI::EventsManager::isEventTriggered(Event event)
{
    return std::find(_eventsList.begin(), _eventsList.end(), event) != _eventsList.end();
}

GUI::EventsManager &GUI::EventsManager::getInstance()
{
    static EventsManager instance;
    return instance;
}

void GUI::EventsManager::addWorldMousePos(Vector2F mousePos)
{
    _worldMousePos = mousePos;
}

const GUI::Vector2F &GUI::EventsManager::getWorldMousePos()
{
    return _worldMousePos;
}

