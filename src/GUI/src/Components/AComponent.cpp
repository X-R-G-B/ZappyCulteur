/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** AComponent
*/

#include "AComponent.hpp"

namespace GUI {
    namespace Components {

        const std::string &AComponent::getId() const {
            return _id;
        }

        CompType AComponent::getType() const {
            return _type;
        }

    }
}
