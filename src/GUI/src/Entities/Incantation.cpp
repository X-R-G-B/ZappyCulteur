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
        static constexpr unsigned int width = 100;
        static constexpr unsigned int height = 100;
        Incantation::Incantation(
            const std::string &id,
            const Vector2F &position,
            EntityOrientation orientation)
            : AEntity(
                id,
                position,
                Vector2F(0, 0),
                Vector2F(1, 1),
                EntityType::INCANTATION,
                orientation
            )
        {
            initIncantationSprite();
        }

        Incantation::~Incantation()
        {
        }

        void Incantation::initIncantationSprite()
        {
            try  {
                _texture.loadFromFile(incantationPath);
                _components.push_back(std::make_shared<GUI::Components::Sprite>(
                    _id,
                    _texture,
                    incantationLayer,
                    _position,
                    width,
                    height
                ));
                _entityCompType.push_back(Components::CompType::SPRITE);
            } catch (std::exception &e) {
                std::cerr << e.what() << std::endl;
            }
        }

        void Incantation::update([[maybe_unused]] double deltaTime)
        {
            // Update the sprite animation
        }

        void Incantation::endIncantation([[maybe_unused]] int result)
        {
            std::size_t level = 0;
            for (auto &it : _trantorians) {
                level = it->getLevel();
                it->setLevel(level + 1);
            }
        }

        void Incantation::addTrantorian(std::shared_ptr<Trantorian> trantorian)
        {
            _trantorians.push_back(trantorian);
        }
    }
}
