/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** AComponent
*/

#pragma once

#include "IComponent.hpp"

namespace GUI {
    namespace Components {
        class AComponent : public IComponent {
            public:
                virtual const std::string &getId() const final;
                virtual CompType getType() const  final;
            protected:
                AComponent(const std::string &id, CompType type);
                std::string _id;
                CompType _type;
        };
    }
}
