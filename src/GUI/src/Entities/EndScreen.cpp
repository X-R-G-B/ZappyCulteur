/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** EndScreen
*/

#include "Components/Sprite.hpp"
#include "Components/Text.hpp"
#include "EndScreen.hpp"

namespace GUI {
    namespace Entities {
        static const std::string filePath = "src/GUI/assets/menu/BeautifulSteve.png";
        static const std::size_t endScreenLayer = 500;
        static const std::string endScreenId = "EndScreen";
        static const std::string textId = "TeamName";

        EndScreen::EndScreen(const std::string &id,
                                const Vector2F &position,
                                unsigned int width,
                                unsigned int height,
                                EntityOrientation orientation,
                                const std::string &teamName)
            : AEntity(
                id,
                position,
                Vector2F(0, 0),
                Vector2F(1, 1),
                EntityType::INCANTATION,
                orientation
            ),
            _teamName(teamName),
            _width(width),
            _height(height)
        {
        }

        EndScreen::~EndScreen()
        {
        }

        void EndScreen::update([[maybe_unused]] double deltaTime)
        {
        }

        void EndScreen::initEndScreenSprite()
        {
            GUI::Color color(0, 0, 0, 255);

            try {
                _texture.loadFromFile(filePath);
                std::shared_ptr<GUI::Components::Sprite> sprite = std::make_shared<GUI::Components::Sprite>(
                    endScreenId,
                    _texture,
                    endScreenLayer,
                    Vector2F(0, 0),
                    _width,
                    _height,
                    Components::CompType::HUDSPRITE
                );
                auto text = std::make_shared<GUI::Components::Text>(
                    textId, _teamName, Vector2F(50, 50), color, 30, Components::CompType::HUDTEXT
                );
                _components.clear();
                _components.push_back(sprite);
                _entityCompType.push_back(Components::CompType::HUDSPRITE);
                _components.push_back(text);
                _entityCompType.push_back(Components::CompType::HUDTEXT);
            } catch (std::exception &e) {
                std::cerr << e.what() << std::endl;
            }
        }
    }
}
