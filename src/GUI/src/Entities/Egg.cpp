/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** egg
*/

#include "Egg.hpp"
#include "Sprite.hpp"

namespace GUI {
    namespace Entities {
        
        static constexpr int eggSize = 42;
        static constexpr int eggScale = 1;
        static constexpr int eggRotation = 0;
        static constexpr int eggLayer = 100;
        static const std::string spriteIdSuffix = "_EggBody";
        static const std::string eggPath = "src/GUI/assets/bees/egg.png";

        Egg::Egg(
            const std::string &id,
            const Vector2F &position
        ) :
            AEntity(
                id,
                position,
                Vector2F(eggRotation, eggRotation),
                Vector2F(eggScale, eggScale),
                EntityType::EGG,
                EntityOrientation::LEFT
            )
        {
            initSprites();
        }

        void Egg::update(double deltaTime)
        {
        }

        void Egg::initSprites()
        {
            if (!_texture.loadFromFile(eggPath)) {
                throw std::runtime_error("Cannot load texture");
            }
            auto sprite = std::make_shared<GUI::Components::Sprite>(
                _id + spriteIdSuffix,
                _texture,
                eggLayer,
                _position,
                eggSize,
                eggSize
            );
            _components.push_back(sprite);
        }
    }
}
