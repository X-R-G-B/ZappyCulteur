/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** Color
*/

#pragma once
#include <cstdint>

namespace GUI {
    class Color {
        public:
            Color(
                std::uint8_t red,
                std::uint8_t green,
                std::uint8_t blue,
                std::uint8_t alpha = 255
            );
            ~Color() = default;
            std::uint8_t getRed() const;
            std::uint8_t getGreen() const;
            std::uint8_t getBlue() const;
            std::uint8_t getAlpha() const;
            void setRed(std::uint8_t red);
            void setGreen(std::uint8_t green);
            void setBlue(std::uint8_t blue);
            void setAlpha(std::uint8_t alpha);

        private:
            std::uint8_t _red;
            std::uint8_t _green;
            std::uint8_t _blue;
            std::uint8_t _alpha;
    };
}
