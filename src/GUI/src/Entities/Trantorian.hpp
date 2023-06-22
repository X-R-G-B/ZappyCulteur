/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** Trantorian
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <chrono>
#include <vector>
#include "AEntity.hpp"
#include "Sprite.hpp"
#include "Text.hpp"

namespace GUI {
    namespace Entities {
        class Trantorian : public AEntity {
            public:
                Trantorian(const std::string &id, const std::string &team,
                const Vector2F &position, EntityOrientation orientation,
                size_t level);
                ~Trantorian() = default;
                void update(double deltaTime) final;
                void setLevel(std::size_t level);
                const std::size_t &getLevel() const;
                void setTeam(const std::string &team);
                const std::string &getTeam() const;
                void setMessage(const std::string &message);
                const std::string &getMessage();
                void setToGo(const Vector2F &toGo);
                const std::chrono::seconds getDispawnTime();
                void setDead(bool dead);
                bool getDead();
                void setDispawned(bool dispawn);
                bool getDispawned();
                void resetMessage();

            private:
                static constexpr int beeSpeed = 200;
                static constexpr int beeAnimationDead = 2;
                static constexpr int levelFontSize = 26;
                static constexpr int teamFontSize = 20;
                static constexpr float levelYOffset = 35;
                static constexpr int messageFontSize = 20;
                static constexpr float messageYOffset = 50;
                static constexpr unsigned int beeWidth = 60;
                static constexpr unsigned int beeHeight = 60;
                static constexpr float teamYOffset = beeHeight - 5;
                void initDeathClock();
                void createTextComponent();
                void updatePosition(double deltaTime);
                void updateComponents();
                void updateText(
                const std::shared_ptr<GUI::Components::IComponent> &comp);
                void initSprites();
                size_t _level;
                std::string _team;
                std::string _message;
                sf::Texture _texture;
                Vector2F _direction;
                Vector2F _toGo;
                float _speed;
                bool _isDead;
                bool _isDispawned;
                std::chrono::seconds _timeDispawn;
                std::chrono::time_point<std::chrono::system_clock> _deathClock;
        };
    } // namespace Entities
} // namespace GUI
