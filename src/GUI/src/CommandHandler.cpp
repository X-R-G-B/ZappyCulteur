/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** CommandHandler
*/

#include <iostream>
#include <sstream>
#include "CommandHandler.hpp"
#include "Floor.hpp"
#include "Ressources.hpp"
#include "Trantorian.hpp"
#include "IEntity.hpp"

namespace GUI {
    namespace CommandHandler {
        static const std::unordered_map<std::string, COMMAND_TYPE> commandProtocol = {
            {"msz", COMMAND_TYPE::MAP_SIZE},
            {"bct", COMMAND_TYPE::MAP_CONTENT},
            {"pnw", COMMAND_TYPE::NEW_PLAYER}
        };

        CommandHandler::CommandHandler(std::shared_ptr<Entities::EntitiesManager> entityManager)
            : _entityManager(entityManager), _toCall({
                {COMMAND_TYPE::MAP_SIZE, &CommandHandler::setMapSize},
                {COMMAND_TYPE::NEW_PLAYER, &CommandHandler::setNewPlayer},
                {COMMAND_TYPE::MAP_CONTENT, &CommandHandler::setRessources}
            })
        {}

        void CommandHandler::update(const std::vector<std::string> &commands)
        {
            COMMAND_TYPE commandKey;
            std::function<bool(CommandHandler &, const std::string &)> functionToCall;

            for (const auto &command : commands) {
                commandKey = getCommandType(command);
                auto elem = _toCall.at(commandKey);
                if (std::invoke(elem, *this, command) == false) {
                    std::cout << "Error while executing this command : " + command << std::endl;
                }
            }
        }

        COMMAND_TYPE CommandHandler::getCommandType(const std::string &command)
        {
            for (const auto &it : commandProtocol) {
                if (command.find(it.first) != std::string::npos) {
                    return (it.second);
                }
            }
            return (COMMAND_TYPE::UNKNOW_COMMAND);
        }

        bool CommandHandler::setMapSize(const std::string &command)
        {
            std::stringstream ss(command);
            unsigned int x = 0;
            unsigned int y = 0;
            std::string cmd;
            
            if (!(ss >> cmd >> x >> y)) {
                return (false);
            }
            if (_entityManager->doesEntityExist("Floor") == true) {
                _entityManager->killEntityById("Floor");
            }
            _entityManager->addEntity(std::make_shared<Entities::Floor>(
                "Floor",
                Vector2F(0, 0),
                x,
                y)
            );
            return (true);
        }

        bool CommandHandler::setNewPlayer(const std::string &command)
        {
            std::stringstream ss(command);
            std::string cmd;
            std::string id;
            float x = 0;
            float y = 0;
            int orientation = 0;
            Entities::EntityOrientation enumOrientation = Entities::EntityOrientation::UP;
            size_t level = 0;
            std::string teamName;

            if (!(ss >> cmd >> id >> x >> y >> orientation >> level >> teamName)
                || orientation < 0 || orientation > 3) {
                return (false);
            }
            id = "Player_" + id;
            if (_entityManager->doesEntityExist(id) == true) {
                _entityManager->killEntityById(id);
            }
            enumOrientation = static_cast<Entities::EntityOrientation>(orientation);

            _entityManager->addEntity(std::make_shared<Entities::Trantorian>(
                id,
                teamName,
                Vector2F(x * TILE_SIZE, y * TILE_SIZE),
                enumOrientation,
                level
            ));
            return (true);
        }

        bool CommandHandler::setRessources(const std::string &command)
        {
            std::shared_ptr<GUI::Entities::IEntity> entity;
            std::stringstream ss(command);
            int x = 0;
            int y = 0;
            int q0 = 0;
            int q1 = 0;
            int q2 = 0;
            int q3 = 0;
            int q4 = 0;
            int q5 = 0;
            int q6 = 0;
            std::string cmd;
            if (_entityManager->doesEntityExist("Floor") == true) {
                entity = _entityManager->getEntityById("Floor");
            } else {
                return (false);
            }

            auto floor = std::static_pointer_cast<GUI::Entities::Floor>(entity);
            ss >> cmd >> x >> y >> q0 >> q1 >> q2 >> q3 >> q4 >> q5 >> q6;
            if (q0 > 0) {
                floor->createRessource(x, y, Entities::RessourcesType::FOOD);
            }
            if (q1 > 0) {
                floor->createRessource(x, y, Entities::RessourcesType::LINEMATE);
            }
            if (q2 > 0) {
                floor->createRessource(x, y, Entities::RessourcesType::DERAUMERE);
            }
            if (q3 > 0) {
                floor->createRessource(x, y, Entities::RessourcesType::SIBUR);
            }
            if (q4 > 0) {
                floor->createRessource(x, y, Entities::RessourcesType::MENDIANE);
            }
            if (q5 > 0) {
                floor->createRessource(x, y, Entities::RessourcesType::PHIRAS);
            }
            if (q6 > 0) {
                floor->createRessource(x, y, Entities::RessourcesType::THYSTAME);
            }
            return (true);
        }
    }
}
