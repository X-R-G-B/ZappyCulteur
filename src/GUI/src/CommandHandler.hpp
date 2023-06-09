/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** CommandHandler
*/

#pragma once

#include <memory>
#include <vector>
#include <string>
#include <unordered_map>
#include <functional>
#include "EntitiesManager.hpp"

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
            EGG_PLAYER_CONNECTED,
            EGG_DEATH,
            TIME_UNIT_REQUEST,
            TIME_UNIT_MODIFICATION,
            GAME_END,
            SERVER_MESSAGE,
            UNKNOW_COMMAND,
            COMMAND_PARAMETER
        };

        /**
         * @class CommandHandler
         * @brief Handles commands and their execution based on a GUI protocol.
         *
         * The CommandHandler class is responsible of handling commands and executing
         * the appropriate functions based on a command protocol. It supports registering
         * different command types with corresponding functions for execution.
         */
        class CommandHandler {
        public:
            /**
             * @brief Constructor for CommandHandler.
             * @param entityManager A shared pointer to the EntityManager.
             */
            CommandHandler(std::shared_ptr<Entities::EntitiesManager> entityManager);

            /**
             * @brief Destructor for CommandHandler.
             */
            ~CommandHandler() = default;

            /**
             * @brief Update enities inside EntityManager based on the command inside the vector.
             * The CommandHndler will recognize wich type of command it is and will parse.
             * When data are parsed the entities will be updatr with those.
             * @param commands A vector of commands to process and execute.
             */
            void update(const std::vector<std::string> &commands);

        protected:
        private:
            /**
             * @brief Retrieves the command type based on the command string.
             * @param command The command string.
             * @return The corresponding command type.
             */
            COMMAND_TYPE getCommandType(const std::string& command);

            /**
             * @brief Sets the map entity size based on the command.
             * @param command The command string.
             * @return True if the map size was set successfully, false otherwise.
             */
            bool setMapSize(const std::string &command);

            /**
             * @brief Sets the new player entity based on the command.
             * @param command The command string.
             * @return True if the new player was set successfully, false otherwise.
             */
            bool setNewPlayer(const std::string &command);

            /**
             * @brief Sets the resources for an entity based on the command.
             * @param command The command string. The format and content of this string
             * should follow the GUI protocol.
             * @return True if the resources were set successfully, false otherwise. 
             * The method may return false if the command string is not properly formatted or if there is a problem updating the entity in the EntityManager.
             */
            bool setRessources(const std::string &command);

            /**
             * @brief Sets the player position based on the command.
             * @param command The command string.
             * @return True if the player position was set successfully, false otherwise.
             */
            bool setPlayerPosition(const std::string &command);

            bool unknowCommand(const std::string &command);

            std::shared_ptr<Entities::EntitiesManager> _entityManager;
            const std::unordered_map<COMMAND_TYPE, std::function<bool(CommandHandler &, const std::string &)>> _toCall;
        };
    }
}
