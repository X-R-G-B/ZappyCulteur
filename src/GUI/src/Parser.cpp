/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** Parser
*/

#include "Parser.hpp"

namespace GUI {
    namespace Parser {

        
        Parser::Parser(std::shared_ptr<EntityManager> entityManager) :
            // Is good implementation ?
            //if you prefer, use std::bind to bind the method
            _entityManager(entityManager),
            _commandToCall({
                {COMMAND_TYPE::MAP_SIZE, &Parser::setMapSize},
                {COMMAND_TYPE::PLAYER_LEVEL, &Parser::setPlayerLevel}
            })
        {}

        Parser::~Parser()
        {
        }

        void Parser::update(std::vector<std::string> &commands)
        {
            while (!commands.empty()) {

                commands.pop_back();
            }
        }

        COMMAND_TYPE Parser::checkCommandType(const std::string &command)
        {
            return (COMMAND_TYPE::UNKNOW_COMMAND);
        }

        bool Parser::setMapSize(std::string &command)
        {
            return (true);
        }

        bool Parser::setPlayerLevel(std::string &command)
        {
            return (true);
        }
    }
}
