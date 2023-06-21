/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** CommandHandler
*/

#pragma once

#include <functional>
#include <memory>
#include <string>
#include <vector>
#include "EntitiesManager.hpp"
#include "NetworkManager.hpp"
#include <unordered_map>

namespace GUI {
    namespace CommandHandler {
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
            EGG_LAYING,
            EGG_LAID,
            RESSOURCE_COLLECTING,
            RESSOURCE_DROPPING,
            EGG_PLAYER_CONNECTED,
            EGG_DEATH,
            TIME_UNIT_REQUEST,
            TIME_UNIT_MODIFICATION,
            GAME_END,
            SERVER_MESSAGE,
            UNKNOW_COMMAND,
            COMMAND_PARAMETER,
            COMMAND_WELCOME
        };

        /**
         * @class CommandHandler
         * @brief Handles commands and their execution based on a GUI protocol.
         *
         * The CommandHandler class is responsible of handling commands and
         * executing the appropriate functions based on a command protocol. It
         * supports registering different command types with corresponding
         * functions for execution.
         */
        class CommandHandler {
            public:
                /**
                 * @brief Constructor for CommandHandler.
                 * @param entityManager A shared pointer to the EntityManager.
                 */
                CommandHandler(
                std::shared_ptr<Entities::EntitiesManager> entityManager,
                std::function<void(const std::string &)> sendToServerFunc);

                /**
                 * @brief Destructor for CommandHandler.
                 */
                ~CommandHandler() = default;

                /**
                 * @brief Update enities inside EntityManager based on the
                 * command inside the vector. The CommandHndler will recognize
                 * wich type of command it is and will parse. When data are
                 * parsed the entities will be updatr with those.
                 * @param commands A vector of commands to process and execute.
                 */
                void update(const std::vector<std::string> &commands);

            protected:
            private:
                /**
                 * @brief Retrieves the command type based on the command
                 * string.
                 * @param command The command string.
                 * @return The corresponding command type.
                 */
                COMMAND_TYPE getCommandType(const std::string &command);

                /**
                 * @brief Sets the map entity size based on the command.
                 * @param command The command string.
                 * @return True if the map size was set successfully, false
                 * otherwise.
                 */
                bool setMapSize(const std::string &command);

                /**
                 * @brief Sets the new player entity based on the command.
                 * @param command The command string.
                 * @return True if the new player was set successfully, false
                 * otherwise.
                 */
                bool setNewPlayer(const std::string &command);

                /**
                 * @brief Sets the resources for an entity based on the command.
                 * @param command The command string. The format and content of
                 * this string should follow the GUI protocol.
                 * @return True if the resources were set successfully, false
                 * otherwise. The method may return false if the command string
                 * is not properly formatted or if there is a problem updating
                 * the entity in the EntityManager.
                 */
                bool setRessources(const std::string &command);

                /**
                 * @brief Sets the player position based on the command.
                 * @param command The command string.
                 * @return True if the player position was set successfully,
                 * false otherwise.
                 */
                bool setPlayerPosition(const std::string &command);

                /**
                 * @brief Sets the egg position based on the command.
                 * @param command The command string.
                 * @return True if the egg position was set successfully, false
                 * otherwise.
                 */
                bool setEggPosition(const std::string &command);

                /**
                 * @brief Kill the egg based on the command.
                 * @param command The command string.
                 * @return True if the egg was killed successfully, false
                 * otherwise.
                 */
                bool setEggDie(const std::string &command);

                /**
                 * @brief Receive WELCOME and send GRAPHIC command.
                 * @param command The command string.
                 * @return True if the connection was successful, false
                 * otherwise.
                 */
                bool receiveFirstConnexion(const std::string &command);

                bool setPlayerDeath(const std::string &command);

                bool startIncantation(const std::string &command);

                bool endGame(const std::string &command);

                bool endIncantation(const std::string &command);

                bool broadcastMessage(const std::string &command);

                bool unknowCommand(const std::string &command);

                /**
                 * @brief Drop a ressource based on the command.
                 * @param command The command string.
                 * @return True if the ressource was dropped successfully, false
                 * otherwise.
                 */
                bool setRessourceDropping(const std::string &command);

                /**
                 * @brief Player collect a ressource based on the command.
                 * @param command The command string.
                 * @return True if the ressource was collected successfully,
                 * false otherwise.
                 */
                bool setRessourceCollecting(const std::string &command);

                /**
                 * @brief Handle id and map size.
                 * @param command The command string.
                 * @return True if the command was handled successfully, false
                 * otherwise.
                 */
                bool handleIdandMapSize(const std::string &command);

                std::shared_ptr<Entities::EntitiesManager> _entityManager;
                const std::unordered_map<COMMAND_TYPE,
                std::function<bool(CommandHandler &, const std::string &)>>
                _toCall;
                std::function<void(const std::string &)> _sendToServerFunc;
                std::size_t _connexionCmdRemaining;
        };
    } // namespace CommandHandler
} // namespace GUI
