/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** Trantorian
*/

#pragma once

#include "AEntity.hpp"

namespace GUI {
    namespace Entities {
        class Trantorian : public AEntity {
            public:
                Trantorian(const std::string &id);
                ~Trantorian() = default;
                void update() override;
                void setLevel(int level);
                int getLevel() const;
                void setTeam(const std::string &team);
                const std::string &getTeam() const;
            private:
                int _level;
                std::string _team;
                //sprites, textures, 3D models, sounds, rect, etc...
        };
    }
}
