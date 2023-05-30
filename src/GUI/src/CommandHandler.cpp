/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** CommandHandler
*/

#include <iostream>
#include "CommandHandler.hpp"

namespace GUI {
    namespace CommandHandler {
        static const std::unordered_map<std::string, COMMAND_TYPE> commandProtocol = {
            {"msz", COMMAND_TYPE::MAP_SIZE}
        };

        CommandHandler::CommandHandler(std::shared_ptr<EntityManager> entityManager)
            : _entityManager(entityManager), _toCall({
                {COMMAND_TYPE::MAP_SIZE, &CommandHandler::setMapSize}
            })
        {}

        void CommandHandler::update(std::vector<std::string> &commands)
        {
            std::string command;
            COMMAND_TYPE commandKey;
            std::function<bool(CommandHandler &, std::string &)> functionToCall;

            while (!commands.empty()) {
                command = commands.back();
                command.erase(command.end() - 1);
                commandKey = getCommandType(command);
                auto elem = _toCall.at(commandKey);
                if (std::invoke(elem, *this, command) == false) {
                    std::cout << "Error while executing this command : " + command << std::endl;
                }
                commands.pop_back();
            }
        }

        COMMAND_TYPE CommandHandler::getCommandType(const std::string &command)
        {
            for (const auto it : commandProtocol) {
                if (command.find(it.first) != std::string::npos) {
                    return (it.second);
                }
            }
            return (COMMAND_TYPE::UNKNOW_COMMAND);
        }

        bool CommandHandler::setMapSize(std::string &command)
        {
            std::size_t spacePos = command.find(" ");
            std::string numbers;

            if (spacePos == std::string::npos) {
                return (false);
            }
            numbers = command.substr(spacePos);
            spacePos = command.find(" ");
            if (spacePos == std::string::npos) {
                return (false);
            }
            std::string x = numbers.substr(1, spacePos);
            std::string y = numbers.substr(spacePos + 1);
            //todo fill the entity
            return (true);
        }
    }
}
