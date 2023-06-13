/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** Incantation
*/

#include "Components/Sprite.hpp"
#include "Incantation.hpp"

namespace GUI {
    namespace Entities {
        static const std::string incantationPath = "path"; // Future path of the incantation sprite
        static const std::size_t incantationLayer = 100;
        Incantation::Incantation(
            const std::string &id,
            const Vector2F &position,
            EntityOrientation orientation,
            std::vector<std::shared_ptr<Trantorian>> &trantorians)
            : AEntity(
                id,
                position,
                Vector2F(0, 0),
                Vector2F(1, 1),
                EntityType::INCANTATION,
                orientation
            ),
            _trantorians(trantorians)
        {
            // Init texture
        }

        Incantation::~Incantation()
        {
        }

        void Incantation::update(double deltaTime)
        {
            // Update the sprite animation
        }

        void Incantation::endIncantation(bool result)
        {
            if (result) {
                std::size_t level = 0;
                for (auto &it : _trantorians) {
                    level = it->getLevel();
                    it->setLevel(level + 1);
                }
            }
        }
    }
}
