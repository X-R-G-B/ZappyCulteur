/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** Trantorian
*/

#include "Trantorian.hpp"

namespace GUI {
    namespace Entities {
        Trantorian::Trantorian(const std::string &id) :
            _level(1),
            _team("")
        {
            _type = EntityType::TRANTORIAN;
            _id = id;
        }

        void Trantorian::update()
        {
            // See later for rect etc...
        }

        void Trantorian::setLevel(int level)
        {
            _level = level;
        }

        int Trantorian::getLevel() const
        {
            return _level;
        }

        void Trantorian::setTeam(const std::string &team)
        {
            _team = team;
        }

        const std::string &Trantorian::getTeam() const
        {
            return _team;
        }
    }
}