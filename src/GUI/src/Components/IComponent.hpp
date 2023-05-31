/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** IComponent
*/

#pragma once

#include <string>

namespace GUI {
    namespace Components {
        enum class CompType {
            UNKNOW,
            SPRITE,
            TEXTURE,
            TEXT,
            MUSIC,
            SOUND,
        };

        class IComponent {
            public:
                ~IComponent() = default;
                virtual const std::string &getId() const = 0;
                virtual const CompType getType() const = 0;
        };
    }
}
