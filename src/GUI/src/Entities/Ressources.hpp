/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** Ressources
*/

#pragma once

#include "AEntity.hpp"

namespace GUI {
    namespace Entities {
        enum class RessourcesType {
            FOOD,
            LINEMATE,
            DERAUMERE,
            SIBUR,
            MENDIANE,
            PHIRAS,
            THYSTAME
        };
        bool operator<(Entities::RessourcesType rt, int nbr);
        bool operator<(int nbr, Entities::RessourcesType rt);
        bool operator>(Entities::RessourcesType rt, int nbr);
        bool operator>(int nbr, Entities::RessourcesType rt);
    }
}
