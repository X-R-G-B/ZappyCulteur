/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** Incantation
*/

#include "Components/Sprite.hpp"
#include "Incantation.hpp"
#include "Floor.hpp"

namespace GUI {
    namespace Entities {
        static const std::string incantationPath = "src/GUI/assets/bees/evolution.png";
        static const std::size_t incantationLayer = 100;
        static const std::string spriteIncantationId = "IncantationSprite";
        static constexpr unsigned int width = 176.4;
        static constexpr unsigned int height = 104.4;
        static constexpr unsigned int rectWidth = 96;
        static constexpr unsigned int rectHeight = 58;
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
            ),
            _timeSinceLastRectChange(0)
        {
            initIncantationSprite();
        }

        Incantation::~Incantation()
        {
        }

        void Incantation::initIncantationSprite()
        {
            try {
                _texture.loadFromFile(incantationPath);
                std::shared_ptr<GUI::Components::Sprite> sprite = std::make_shared<GUI::Components::Sprite>(
                    spriteIncantationId,
                    _texture,
                    incantationLayer,
                    Vector2F(_position.x * TILE_SIZE, _position.y * TILE_SIZE),
                    width,
                    height
                );
                sprite->setRect(sf::IntRect(0, 0, rectWidth, rectHeight));
                _components.push_back(sprite);
                _entityCompType.push_back(Components::CompType::SPRITE);
            } catch (std::exception &e) {
                std::cerr << e.what() << std::endl;
            }
        }

        void Incantation::update(double deltaTime)
        {
            _timeSinceLastRectChange += deltaTime;
            if (_timeSinceLastRectChange >= 0.2) {
                updateSpriteRect();
            }
        }

        void Incantation::updateSpriteRect()
        {
            _timeSinceLastRectChange = 0;
            std::shared_ptr<GUI::Components::Sprite> sprite;
            for (auto &it : _components) {
                if (it->getId() == spriteIncantationId) {
                    sprite = std::static_pointer_cast<GUI::Components::Sprite>(it);
                    break;
                }
            }
            if (sprite == nullptr) {
                return;
            }
            sf::IntRect rect = sprite->getRect();
            if (rect.left == 0) {
                rect.left = rectWidth;
            } else {
                rect.left = 0;
            }
            sprite->setRect(rect);
        }

        void Incantation::endIncantation(int result)
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
