/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** Parser
*/

#pragma once

#include <memory>
#include <vector>
#include <string>
#include <unordered_map>
#include <functional>
#include "EntityManager.hpp"

namespace GUI {
    namespace Parser {
        enum class COMMAND_TYPE {
            MAP_SIZE,
            TILE,
            MAP_CONTENT,
            TEAM_NAMES,
            NEW_PLAYER,
            PLAYER_POSITION,
            PLAYER_LEVEL,
            PLAYER_INVENTORY,
            PLAYER_DEATH,
            EXPULSION,
            BROADCAST,
            INCANTATION_START,
            INCANTATION_END,
            EGG_LAYING, // A questionner en FU
            EGG_LAID, // A questionner en FU
            RESSOURCE_COLLECTING,
            EGG_PLAYER_CONNECTED, // A questionner en FU
            EGG_DEATH, // A questionner en FU
            TIME_UNIT_REQUEST,
            TIME_UNIT_MODIFICATION,
            GAME_END,
            SERVER_MESSAGE,
            UNKNOW_COMMAND,
            COMMAND_PARAMETER // A questionner en FU
        };

        class Parser {
            public:
                Parser(std::shared_ptr<EntityManager> entityManager);
                ~Parser();

                void update(std::vector<std::string> &commands);

                COMMAND_TYPE checkCommandType(const std::string &command);
            protected:
            private:
                bool setMapSize(std::string &command);

                std::shared_ptr<EntityManager> _entityManager;
                std::unordered_map<COMMAND_TYPE, std::function<bool(GUI::Parser::Parser *)(std::string &)>> _toCall;
        };
    }
}
