/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** Parser
*/

#include "Parser.hpp"

namespace GUI {
    namespace Parser {

        
        Parser::Parser(std::shared_ptr<EntityManager> entityManager)
            // Is good implementation ?
            : _entityManager(entityManager)
        {
            _toCall[COMMAND_TYPE::MAP_SIZE] = &setMapSize;
        }

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
        
    }
}
