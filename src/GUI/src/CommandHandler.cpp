/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** CommandHandler
*/

#include "CommandHandler.hpp"
#include <iostream>
#include <sstream>
#include "Egg.hpp"
#include "Floor.hpp"
#include "IComponent.hpp"
#include "IEntity.hpp"
#include "Incantation.hpp"
#include "Ressources.hpp"
#include "Trantorian.hpp"
#include "Incantation.hpp"
#include "Expulsion.hpp"
#include "EndScreen.hpp"
#include "IEntity.hpp"
#include "Egg.hpp"

namespace GUI {
    namespace CommandHandler {

        static const std::unordered_map<std::string, COMMAND_TYPE>
        commandProtocol = {{"msz", COMMAND_TYPE::MAP_SIZE},
            {"bct", COMMAND_TYPE::MAP_CONTENT}, {"pnw", COMMAND_TYPE::NEW_PLAYER},
            {"pnw", COMMAND_TYPE::NEW_PLAYER},
            {"ppo", COMMAND_TYPE::PLAYER_POSITION},
            {"pie", COMMAND_TYPE::INCANTATION_END},
            {"pic", COMMAND_TYPE::INCANTATION_START},
            {"enw", COMMAND_TYPE::EGG_LAID}, {"edi", COMMAND_TYPE::EGG_DEATH},
            {"ebo", COMMAND_TYPE::EGG_PLAYER_CONNECTED},
            {"pdi", COMMAND_TYPE::PLAYER_DEATH},
            {"pgt", COMMAND_TYPE::RESSOURCE_COLLECTING},
            {"pdr", COMMAND_TYPE::RESSOURCE_DROPPING},
            {"pbc", COMMAND_TYPE::BROADCAST},
            {"seg", COMMAND_TYPE::GAME_END},
            {"smg", COMMAND_TYPE::SERVER_MESSAGE},
            {"suc", COMMAND_TYPE::SERVER_UNKNOW_COMMAND},
            {"pex", COMMAND_TYPE::EXPULSION},
            {"sgt", COMMAND_TYPE::TIME_UNIT_REQUEST},
            {"sst", COMMAND_TYPE::TIME_UNIT_MODIFICATION},
            {"sbp", COMMAND_TYPE::COMMAND_PARAMETER},
            {"pfk", COMMAND_TYPE::EGG_LAYING},
            {"WELCOME", COMMAND_TYPE::COMMAND_WELCOME},
        };

        CommandHandler::CommandHandler(
        std::shared_ptr<Entities::EntitiesManager> entityManager,
        std::function<void(const std::string &)> sendToServer)
            : _entityManager(entityManager),
              _toCall({{COMMAND_TYPE::MAP_SIZE, &CommandHandler::setMapSize},
              {COMMAND_TYPE::NEW_PLAYER, &CommandHandler::setNewPlayer},
              {COMMAND_TYPE::MAP_CONTENT, &CommandHandler::setRessources},
              {COMMAND_TYPE::PLAYER_POSITION,
              &CommandHandler::setPlayerPosition},
              {COMMAND_TYPE::EGG_LAID, &CommandHandler::setEggPosition},
              {COMMAND_TYPE::EGG_DEATH, &CommandHandler::setEggDie},
              {COMMAND_TYPE::EGG_PLAYER_CONNECTED, &CommandHandler::setEggDie},
              {COMMAND_TYPE::PLAYER_DEATH, &CommandHandler::setPlayerDeath},
              {COMMAND_TYPE::INCANTATION_START,
              &CommandHandler::startIncantation},
              {COMMAND_TYPE::INCANTATION_END, &CommandHandler::endIncantation},
              {COMMAND_TYPE::PLAYER_DEATH, &CommandHandler::setPlayerDeath},
              {COMMAND_TYPE::RESSOURCE_COLLECTING,
              &CommandHandler::setRessourceCollecting},
              {COMMAND_TYPE::RESSOURCE_DROPPING,
              &CommandHandler::setRessourceDropping},
              {COMMAND_TYPE::COMMAND_WELCOME,
              &CommandHandler::receiveFirstConnexion},
              {COMMAND_TYPE::GAME_END, &CommandHandler::endGame},
              {COMMAND_TYPE::BROADCAST, &CommandHandler::broadcastMessage},
              {COMMAND_TYPE::SERVER_MESSAGE, &CommandHandler::serverMessage},
              {COMMAND_TYPE::TIME_UNIT_MODIFICATION, &CommandHandler::timeUnitModification},
              {COMMAND_TYPE::SERVER_UNKNOW_COMMAND, &CommandHandler::serverUnknowCommand},
              {COMMAND_TYPE::TIME_UNIT_REQUEST, &CommandHandler::timeUnitRequest},
              {COMMAND_TYPE::EXPULSION, &CommandHandler::expulsion},
              {COMMAND_TYPE::COMMAND_PARAMETER, &CommandHandler::badCommandParameter},
              {COMMAND_TYPE::EGG_LAYING, &CommandHandler::clientForking},
              {COMMAND_TYPE::UNKNOW_COMMAND, &CommandHandler::unknowCommand}}),
              _sendToServerFunc(sendToServer), _connexionCmdRemaining(0), _isReadyToReceive(false)
        {
        }

        static const std::string eggKey = "Egg_";
        static const std::string playerKey = "Player_";
        static const std::string incantationKey = "Incantation_";
        static const std::string invocationStateKo = "ko";
        static const std::string endScreenKey = "EndScreen";

        void CommandHandler::update(const std::vector<std::string> &commands)
        {
            COMMAND_TYPE commandKey;
            std::function<bool(CommandHandler &, const std::string &)>
            functionToCall;

            for (const auto &command : commands) {
                if (_connexionCmdRemaining > 0) {
                    handleIdandMapSize(command);
                    continue;
                }
                commandKey = getCommandType(command);
                auto elem = _toCall.at(commandKey);
                if (std::invoke(elem, *this, command) == false) {
                    std::cout << "Error while executing this command : "
                    + command << std::endl;
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
            _entityManager->addEntity(
            std::make_shared<Entities::Floor>("Floor", Vector2F(0, 0), x, y));
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
            Entities::EntityOrientation enumOrientation =
            Entities::EntityOrientation::UP;
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
            enumOrientation =
            static_cast<Entities::EntityOrientation>(orientation);

            _entityManager->addEntity(
            std::make_shared<Entities::Trantorian>(id, teamName,
            Vector2F(x * TILE_SIZE, y * TILE_SIZE), enumOrientation, level));
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
            std::make_pair(0, Entities::RessourcesType::THYSTAME)};
            int x = 0;
            int y = 0;
            std::string cmd;
            if (_entityManager->doesEntityExist("Floor") == true) {
                entity = _entityManager->getEntityById("Floor");
            } else {
                return (false);
            }

            auto floor = std::static_pointer_cast<GUI::Entities::Floor>(entity);
            if (!(ss >> cmd >> x >> y >> ressources[0].first
                >> ressources[1].first >> ressources[2].first
                >> ressources[3].first >> ressources[4].first
                >> ressources[5].first >> ressources[6].first)) {
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
            Entities::EntityOrientation enumOrientation =
            Entities::EntityOrientation::UP;

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
                auto trantorian =
                std::static_pointer_cast<Entities::Trantorian>(entity);
                enumOrientation =
                static_cast<Entities::EntityOrientation>(orientation);
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
                auto trantorian =
                std::static_pointer_cast<Entities::Trantorian>(entity);
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
            incantationId =
            incantationKey + std::to_string(x) + std::to_string(y);
            try {
                auto incantationEntity =
                std::make_shared<Entities::Incantation>(
                incantationId, Vector2F(x, y), Entities::EntityOrientation::UP);
                while (!playerIds.empty()) {
                    id = playerIds.back();
                    auto entity = _entityManager->getEntityById(playerKey + id);
                    auto trantorian =
                    std::static_pointer_cast<Entities::Trantorian>(entity);
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
            std::string result;
            std::string tmp;
            std::string incantationId;

            if (!(ss >> cmd >> x >> y)) {
                return (false);
            }
            std::cout << ss.str() << std::endl;
            while (ss >> tmp) {
                result.append(tmp);

            }
            incantationId = incantationKey + std::to_string(x) + std::to_string(y);
            try {
                auto entity = _entityManager->getEntityById(incantationId);
                auto incantation =
                std::static_pointer_cast<Entities::Incantation>(entity);
                if (result.find(invocationStateKo) != std::string::npos) {
                    incantation->endIncantation(0);
                } else {
                    std::string nbr = result.substr(result.find(":"));
                    std::size_t level = static_cast<std::size_t>(std::stoi(nbr.substr(1)));
                    incantation->endIncantation(level);
                }
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
            eggId, Vector2F(x * TILE_SIZE, y * TILE_SIZE)));
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

            if (!(ss >> cmd >> id >> ressource)
            || ressource < Entities::RessourcesType::FOOD
            || ressource > Entities::RessourcesType::THYSTAME) {
                return false;
            }
            Entities::RessourcesType rt =
            static_cast<Entities::RessourcesType>(ressource);
            std::shared_ptr<GUI::Entities::IEntity> entity;
            try {
                floorEntity = _entityManager->getEntityById("Floor");
                playerEntity = _entityManager->getEntityById(playerKey + id);
            } catch (const Entities::EntitiesManagerException &e) {
                std::cerr << e.what() << std::endl;
                return false;
            }
            auto floor =
            std::static_pointer_cast<GUI::Entities::Floor>(floorEntity);
            Vector2F tile = {playerEntity->getPosition().x == 0
            ? 0
            : playerEntity->getPosition().x / TILE_SIZE,
            playerEntity->getPosition().y == 0
            ? 0
            : playerEntity->getPosition().y / TILE_SIZE};
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

            if (!(ss >> cmd >> id >> ressource)
            || ressource < Entities::RessourcesType::FOOD
            || ressource > Entities::RessourcesType::THYSTAME) {
                return false;
            }
            Entities::RessourcesType rt =
            static_cast<Entities::RessourcesType>(ressource);
            std::shared_ptr<GUI::Entities::IEntity> entity;
            try {
                floorEntity = _entityManager->getEntityById("Floor");
                playerEntity = _entityManager->getEntityById(playerKey + id);
            } catch (const Entities::EntitiesManagerException &e) {
                std::cerr << e.what() << std::endl;
                return false;
            }
            auto floor =
            std::static_pointer_cast<GUI::Entities::Floor>(floorEntity);
            auto player =
            std::static_pointer_cast<GUI::Entities::Trantorian>(playerEntity);
            floor->createRessource(player->getPosition().x == 0
            ? 0
            : static_cast<unsigned int>(player->getPosition().x / TILE_SIZE),
            player->getPosition().y == 0
            ? 0
            : static_cast<unsigned int>(player->getPosition().y / TILE_SIZE),
            rt);
            return true;
        }

        bool CommandHandler::serverUnknowCommand([[maybe_unused]]const std::string &command)
        {
            std::cout << "Server did not recognize our command" << std::endl;
            return (true);
        }

        bool CommandHandler::endGame(const std::string &command)
        {
            std::stringstream ss(command);
            std::string cmd;
            std::string team;

            if (!(ss >> cmd >> team)) {
                return (false);
            }
            auto endScreenEntity = std::make_shared<Entities::EndScreen>(
                endScreenKey,
                Vector2F(0, 0),
                team
            );
            try {
                endScreenEntity->initEndScreenSprite();
                _entityManager->addEntity(endScreenEntity);
            } catch (const Entities::EntitiesManagerException &e) {
                std::cerr << e.what() << std::endl;
                return false;
            }
            return (true);
        }

        bool CommandHandler::receiveFirstConnexion(const std::string &)
        {
            _sendToServerFunc("GRAPHIC\n");
            _connexionCmdRemaining = 2;
            return true;
        }

        bool CommandHandler::broadcastMessage(const std::string &command)
        {
            std::stringstream ss(command);
            std::string cmd;
            std::string id;
            std::string tmp;
            std::string message;

            if (!(ss >> cmd >> id)) {
                return (false);
            }
            while (ss >> tmp) {
                message.append(tmp + " ");
            }
            try {
                auto entity = _entityManager->getEntityById(playerKey + id);
                auto trantorian =
                std::static_pointer_cast<Entities::Trantorian>(entity);
                trantorian->setMessage(message);
                trantorian->resetMessage();
            } catch (const Entities::EntitiesManagerException &e) {
                std::cerr << e.what() << std::endl;
                return false;
            }
            return (true);
        }
        
        bool CommandHandler::timeUnitModification(const std::string &command)
        {
            std::stringstream ss(command);
            std::string cmd;
            std::size_t time = 0;

            if (!(ss >> cmd >> time)) {
                return (false);
            }
            std::cout << "Time server modification : " << time << std::endl;
            return (true);
        }


        bool CommandHandler::timeUnitRequest(const std::string &command)
        {
            std::stringstream ss(command);
            std::string cmd;
            std::size_t time;

            if (!(ss >> cmd >> time)) {
                return (false);
            }
            // Change the time unit get
            return (true);
        }

        bool CommandHandler::serverMessage(const std::string &command)
        {
            std::stringstream ss(command);
            std::string cmd;
            std::string tmp;
            std::string message;

            if (!(ss >> cmd)) {
                return (false);
            }
            while (ss >> tmp) {
                message.append(tmp);
            }
            std::cout << "Message from server : " << message << std::endl;
            return (true);
        }

        bool CommandHandler::badCommandParameter([[maybe_unused]]const std::string &command)
        {
            std::cout << "Sending bad parameters to server." << std::endl;
            return (true);
        }

        bool CommandHandler::expulsion(const std::string &command)
        {
            std::stringstream ss(command);
            std::string cmd;
            std::string id;
            std::string trantorianId;

            if (!(ss >> cmd >> id)) {
                return (false);
            }
            trantorianId += playerKey + id;
            try {
                auto player = _entityManager->getEntityById(trantorianId);
                auto expulsionEntity = std::make_shared<Entities::Expulsion>(
                    id, player->getPosition());
                expulsionEntity->initExpulsionSprite();
                _entityManager->addEntity(expulsionEntity);
            } catch (const Entities::EntitiesManagerException &e) {
                std::cerr << e.what() << std::endl;
                return false;
            }
            return (true);
        }

        bool CommandHandler::clientForking(const std::string &command)
        {
            std::stringstream ss(command);
            std::string cmd;
            std::string id;

            if (!(ss >> cmd >> id)) {
                return (false);
            }
            std::cout << "Trantorian " << id << " is forking." << std::endl;
            return (true);
        }

        bool CommandHandler::handleIdandMapSize(const std::string &command)
        {
            std::string newCommand;

            _connexionCmdRemaining -= 1;
            if (_connexionCmdRemaining == 0) {
                newCommand = "msz " + command;
                setMapSize(newCommand);
                if (_entityManager->doesEntityExist("Floor") == false) {
                    _sendToServerFunc("msz\n");
                }
                _isReadyToReceive = true;
            }
            return true;
        }

        bool CommandHandler::getIsReadyToReceive() const
        {
            return _isReadyToReceive;
        }

    } // namespace CommandHandler
} // namespace GUI
