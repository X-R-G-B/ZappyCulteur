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
            HUDSPRITE,
            HUDTEXT,
        };

        class IComponent {
            public:
                ~IComponent() = default;
                /**
                 * @brief get the id of the component
                 */
                virtual const std::string &getId() const = 0;

                /**
                 * @brief get the type of the component
                 */
                virtual CompType getType() const = 0;
        };
    } // namespace Components
} // namespace GUI
