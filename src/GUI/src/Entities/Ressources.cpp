/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** Ressources
*/

#include "Ressources.hpp"

namespace GUI {
    namespace Entities {
        bool operator<(Entities::RessourcesType rt, int nbr)
        {
            return static_cast<int>(rt) < nbr;
        }

        bool operator<(int nbr, Entities::RessourcesType rt)
        {
            return nbr < static_cast<int>(rt);
        }

        bool operator>(Entities::RessourcesType rt, int nbr)
        {
            return static_cast<int>(rt) > nbr;
        }

        bool operator>(int nbr, Entities::RessourcesType rt)
        {
            return nbr > static_cast<int>(rt);
        }
    } // namespace Entities
} // namespace GUI
