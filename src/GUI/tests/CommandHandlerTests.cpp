/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** CommandHandlerTests
*/

#include "../src/EntityManager.hpp"
#include "../src/CommandHandler.hpp"

int main(void)
{
    std::vector<std::string> commands = {
        "msz 10 10\n"
    };
    std::shared_ptr<EntityManager> entityManager;
    GUI::CommandHandler::CommandHandler commandHandler(entityManager);

    commandHandler.update(commands);
}
