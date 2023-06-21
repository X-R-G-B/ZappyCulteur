/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** AComponent
*/

#include "AComponent.hpp"

namespace GUI {
    namespace Components {

        AComponent::AComponent(const std::string &id, CompType type)
            : _id(id), _type(type)
        {
        }

        const std::string &AComponent::getId() const
        {
            return _id;
        }

        CompType AComponent::getType() const
        {
            return _type;
        }

    } // namespace Components
} // namespace GUI
