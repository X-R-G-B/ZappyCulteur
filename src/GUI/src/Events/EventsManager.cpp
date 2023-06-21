/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** Events
*/

#include "EventsManager.hpp"

GUI::EventsManager::EventsManager() :
    _mousePos({0, 0}),
    _worldMousePos({0, 0}),
    _state(GUI::EventsState::FOCUS_UI)
{
}

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
    return std::find(_eventsList.begin(), _eventsList.end(), event)
    != _eventsList.end();
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

std::string GUI::EventsManager::getEventKey(GUI::Event event)
{
   std::string keyStr;

    if (event >= GUI::Event::KEYBOARD_0_PRESSED &&
        event <= GUI::Event::KEYBOARD_9_PRESSED) {
        keyStr = std::to_string(static_cast<int>(event));
    } else if (event >= GUI::Event::KEYBOARD_A_PRESSED &&
        event <= GUI::Event::KEYBOARD_Z_PRESSED) {
        keyStr = static_cast<char>(static_cast<int>(event) + 55);
    } else if (event == GUI::Event::KEYBOARD_DOT_PRESSED) {
        keyStr = ".";
    }
    return keyStr;
}

bool GUI::EventsManager::isFocusedOnUI()
{
    return _state == GUI::EventsState::FOCUS_UI ? true : false;
}

bool GUI::EventsManager::isFocusedOnGame()
{
    return _state == GUI::EventsState::FOCUS_GAME ? true : false;
}

void GUI::EventsManager::setFocusOnUI()
{
    _state = GUI::EventsState::FOCUS_UI;
}

void GUI::EventsManager::setFocusOnGame()
{
    _state = GUI::EventsState::FOCUS_GAME;
}
