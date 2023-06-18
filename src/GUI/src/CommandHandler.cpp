/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** CommandHandler
*/

#include <iostream>
#include <sstream>
#include "CommandHandler.hpp"
#include "IComponent.hpp"
#include "Floor.hpp"
#include "Ressources.hpp"
#include "Trantorian.hpp"
#include "Incantation.hpp"
#include "IEntity.hpp"
#include "Egg.hpp"

namespace GUI {
    namespace CommandHandler {
        static const std::unordered_map<std::string, COMMAND_TYPE> commandProtocol = {
            {"msz", COMMAND_TYPE::MAP_SIZE},
            {"bct", COMMAND_TYPE::MAP_CONTENT},
            {"pnw", COMMAND_TYPE::NEW_PLAYER},
            {"pnw", COMMAND_TYPE::NEW_PLAYER},
            {"ppo", COMMAND_TYPE::PLAYER_POSITION},
            {"pie", COMMAND_TYPE::INCANTATION_END},
            {"pic", COMMAND_TYPE::INCANTATION_START},
            {"enw", COMMAND_TYPE::EGG_LAID},
            {"edi", COMMAND_TYPE::EGG_DEATH},
            {"ebo", COMMAND_TYPE::EGG_PLAYER_CONNECTED},
            {"pdi", COMMAND_TYPE::PLAYER_DEATH},
            {"pgt", COMMAND_TYPE::RESSOURCE_COLLECTING},
            {"pdr", COMMAND_TYPE::RESSOURCE_DROPPING},
            {"WELCOME", COMMAND_TYPE::COMMAND_WELCOME}
        };

        CommandHandler::CommandHandler(
            std::shared_ptr<Entities::EntitiesManager> entityManager,
            std::function<void(const std::string &)> sendToServer)
            : _entityManager(entityManager), _toCall({
                {COMMAND_TYPE::MAP_SIZE, &CommandHandler::setMapSize},
                {COMMAND_TYPE::NEW_PLAYER, &CommandHandler::setNewPlayer},
                {COMMAND_TYPE::MAP_CONTENT, &CommandHandler::setRessources},
                {COMMAND_TYPE::PLAYER_POSITION, &CommandHandler::setPlayerPosition},
                {COMMAND_TYPE::EGG_LAID, &CommandHandler::setEggPosition},
                {COMMAND_TYPE::EGG_DEATH, &CommandHandler::setEggDie},
                {COMMAND_TYPE::EGG_PLAYER_CONNECTED, &CommandHandler::setEggDie},
                {COMMAND_TYPE::PLAYER_DEATH, &CommandHandler::setPlayerDeath},
                {COMMAND_TYPE::INCANTATION_START, &CommandHandler::startIncantation},
                {COMMAND_TYPE::INCANTATION_END, &CommandHandler::endIncantation},
                {COMMAND_TYPE::PLAYER_DEATH, &CommandHandler::setPlayerDeath},
                {COMMAND_TYPE::RESSOURCE_COLLECTING, &CommandHandler::setRessourceCollecting},
                {COMMAND_TYPE::RESSOURCE_DROPPING, &CommandHandler::setRessourceDropping},
                {COMMAND_TYPE::COMMAND_WELCOME, &CommandHandler::receiveFirstConnexion},
                {COMMAND_TYPE::UNKNOW_COMMAND, &CommandHandler::unknowCommand}
            }), _sendToServerFunc(sendToServer)
        {}

        static const std::string eggKey = "Egg_";
        static const std::string playerKey = "Player_";
        static const std::string incantationKey = "Incantation_";

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
                || orientation < Entities::EntityOrientation::UP
                || orientation > Entities::EntityOrientation::LEFT) {
                return (false);
            }
            id = playerKey + id;
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
            std::vector<std::pair<int, Entities::RessourcesType>> ressources = {
                std::make_pair(0, Entities::RessourcesType::FOOD),
                std::make_pair(0, Entities::RessourcesType::LINEMATE),
                std::make_pair(0, Entities::RessourcesType::DERAUMERE),
                std::make_pair(0, Entities::RessourcesType::SIBUR),
                std::make_pair(0, Entities::RessourcesType::MENDIANE),
                std::make_pair(0, Entities::RessourcesType::PHIRAS),
                std::make_pair(0, Entities::RessourcesType::THYSTAME)
            };
            int x = 0;
            int y = 0;
            std::string cmd;
            if (_entityManager->doesEntityExist("Floor") == true) {
                entity = _entityManager->getEntityById("Floor");
            } else {
                return (false);
            }

            auto floor = std::static_pointer_cast<GUI::Entities::Floor>(entity);
            if (!(ss >> cmd >> x >> y >> ressources[0].first >> ressources[1].first >>
                ressources[2].first >> ressources[3].first >> ressources[4].first >>
                ressources[5].first >> ressources[6].first)) {
                return (false);
            }
            for (const auto &it : ressources) {
                if (it.first > 0) {
                    floor->createRessources(x, y, it.second, it.first);
                }
            }
            return (true);
        }

        bool CommandHandler::setPlayerPosition(const std::string &command)
        {
            std::stringstream ss(command);
            std::string cmd;
            std::string id;
            float x = 0;
            float y = 0;
            int orientation = 0;
            Entities::EntityOrientation enumOrientation = Entities::EntityOrientation::UP;

            if (!(ss >> cmd >> id >> x >> y >> orientation)
                || orientation < Entities::EntityOrientation::UP
                || orientation > Entities::EntityOrientation::LEFT) {
                return (false);
            }
            id = playerKey + id;
            if (_entityManager->doesEntityExist(id) == false) {
                return (false);
            }
            try {
                auto entity = _entityManager->getEntityById(id);
                auto trantorian = std::static_pointer_cast<Entities::Trantorian>(entity);
                enumOrientation = static_cast<Entities::EntityOrientation>(orientation);
                trantorian->setOrientation(enumOrientation);
                trantorian->setToGo(Vector2F(x * TILE_SIZE, y * TILE_SIZE));
            } catch (const Entities::EntitiesManagerException &e) {
                std::cerr << e.what() << std::endl;
                return (false);
            }
            return (true);
        }

        bool CommandHandler::setPlayerDeath(const std::string &command)
        {
            std::stringstream ss(command);
            std::string cmd;
            std::string id;

            ss >> cmd >> id;
            try {
                auto entity = _entityManager->getEntityById(playerKey + id);
                auto trantorian = std::static_pointer_cast<Entities::Trantorian>(entity);
                trantorian->setDead(true);
            } catch (const Entities::EntitiesManagerException &e) {
                std::cerr << e.what() << std::endl;
                return (false);
            }
            return (true);
        }

        bool CommandHandler::startIncantation(const std::string &command)
        {
            std::stringstream ss(command);
            std::string cmd;
            std::string incantationId;
            float x = 0;
            float y = 0;
            std::string level;
            std::string id;
            std::vector<std::string> playerIds;

            if (!(ss >> cmd >> x >> y >> level)) {
                return (false);
            }
            while (ss >> id) {
                playerIds.push_back(id);
            }
            incantationId = incantationKey + std::to_string(x) + std::to_string(y);
            try {
                auto incantationEntity = std::make_shared<Entities::Incantation>(incantationId,
                                            Vector2F(x, y), Entities::EntityOrientation::UP);
                while (!playerIds.empty()) {
                    id = playerIds.back();
                    auto entity = _entityManager->getEntityById(playerKey + id);
                    auto trantorian = std::static_pointer_cast<Entities::Trantorian>(entity);
                    incantationEntity->addTrantorian(trantorian);
                    playerIds.pop_back();
                }
                _entityManager->addEntity(incantationEntity);
            } catch (const Entities::EntitiesManagerException &e) {
                std::cerr << e.what() << std::endl;
                return (false);
            }
            return (true);
        }

        bool CommandHandler::endIncantation(const std::string &command)
        {
            std::stringstream ss(command);
            std::string cmd;
            float x = 0;
            float y = 0;
            std::size_t result = 0;
            std::string incantationId;

            if (!(ss >> cmd >> x >> y >> result)) {
                return (false);
            }
            incantationId = incantationKey + std::to_string(x) + std::to_string(y);
            try {
                auto entity = _entityManager->getEntityById(incantationId);
                auto incantation = std::static_pointer_cast<Entities::Incantation>(entity);
                incantation->endIncantation(result);
                _entityManager->killEntityById(incantationId);
            } catch (const Entities::EntitiesManagerException &e) {
                std::cerr << e.what() << std::endl;
                return (false);
            }
            return (true);
        }

        bool CommandHandler::unknowCommand(const std::string &command)
        {
            std::cout << "Command undefined : " << command << std::endl;
            return (true);
        }

        bool CommandHandler::setEggPosition(const std::string &command)
        {
            std::stringstream ss(command);
            std::string cmd;
            std::string eggId;
            std::string playerId;
            float x = 0, y = 0;

            if (!(ss >> cmd >> eggId >> playerId >> x >> y)) {
                return (false);
            }
            eggId = eggKey + eggId;
            if (_entityManager->doesEntityExist(eggId) == true) {
                _entityManager->killEntityById(eggId);
            }
            _entityManager->addEntity(std::make_shared<Entities::Egg>(
                eggId,
                Vector2F(x * TILE_SIZE, y * TILE_SIZE)
            ));
            return (true);
        }

        bool CommandHandler::setEggDie(const std::string &command)
        {
            std::stringstream ss(command);
            std::string cmd;
            std::string eggId;

            if (!(ss >> cmd >> eggId)) {
                return (false);
            }
            eggId = eggKey + eggId;
            if (_entityManager->doesEntityExist(eggId) == true) {
                _entityManager->killEntityById(eggId);
            } else {
                std::cout << "Egg " << eggId << " does not exist" << std::endl;
                return (false);
            }
            return (true);
        }

        bool CommandHandler::setRessourceCollecting(const std::string &command)
        {
            int ressource = 0;
            std::string cmd, id;
            std::stringstream ss(command);
            std::shared_ptr<GUI::Entities::IEntity> floorEntity = nullptr;
            std::shared_ptr<GUI::Entities::IEntity> playerEntity = nullptr;

            if (!(ss >> cmd >> id >> ressource) ||
            ressource < Entities::RessourcesType::FOOD ||
            ressource > Entities::RessourcesType::THYSTAME) {
                return false;
            }
            Entities::RessourcesType rt = static_cast<Entities::RessourcesType>(ressource);
            std::shared_ptr<GUI::Entities::IEntity> entity;
            try {
                floorEntity = _entityManager->getEntityById("Floor");
                playerEntity = _entityManager->getEntityById(playerKey + id);
            } catch (const Entities::EntitiesManagerException &e) {
                std::cerr << e.what() << std::endl;
                return false;
            }
            auto floor = std::static_pointer_cast<GUI::Entities::Floor>(floorEntity);
            Vector2F tile = {
                playerEntity->getPosition().x == 0 ? 0 : playerEntity->getPosition().x / TILE_SIZE,
                playerEntity->getPosition().y == 0 ? 0 : playerEntity->getPosition().y / TILE_SIZE
            };
            floor->removeRessources(tile, rt);
            return true;
        }

        bool CommandHandler::setRessourceDropping(const std::string &command)
        {
            int ressource = 0;
            std::string cmd, id;
            std::stringstream ss(command);
            std::shared_ptr<GUI::Entities::IEntity> floorEntity = nullptr;
            std::shared_ptr<GUI::Entities::IEntity> playerEntity = nullptr;

            if (!(ss >> cmd >> id >> ressource) ||
            ressource < Entities::RessourcesType::FOOD ||
            ressource > Entities::RessourcesType::THYSTAME) {
                return false;
            }
            Entities::RessourcesType rt = static_cast<Entities::RessourcesType>(ressource);
            std::shared_ptr<GUI::Entities::IEntity> entity;
            try {
                floorEntity = _entityManager->getEntityById("Floor");
                playerEntity = _entityManager->getEntityById(playerKey + id);
            } catch (const Entities::EntitiesManagerException &e) {
                std::cerr << e.what() << std::endl;
                return false;
            }
            auto floor = std::static_pointer_cast<GUI::Entities::Floor>(floorEntity);
            auto player = std::static_pointer_cast<GUI::Entities::Trantorian>(playerEntity);
            floor->createRessource(
                player->getPosition().x == 0 ? 0 : static_cast<unsigned int>(player->getPosition().x / TILE_SIZE),
                player->getPosition().y == 0 ? 0 : static_cast<unsigned int>(player->getPosition().y / TILE_SIZE),
                rt
            );
            return true;
        }

        bool CommandHandler::receiveFirstConnexion(const std::string &)
        {
            _sendToServerFunc("GRAPHIC\n");
            return true;
        }
    }
}
