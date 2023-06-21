/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** Color
*/

#include "Color.hpp"
#include <SFML/Graphics.hpp>

namespace GUI {
    Color::Color(
    std::uint8_t red, std::uint8_t green, std::uint8_t blue, std::uint8_t alpha)
        : _red(red), _green(green), _blue(blue), _alpha(alpha)
    {
    }

    std::uint8_t Color::getRed() const
    {
        return _red;
    }

    std::uint8_t Color::getGreen() const
    {
        return _green;
    }

    std::uint8_t Color::getBlue() const
    {
        return _blue;
    }

    std::uint8_t Color::getAlpha() const
    {
        return _alpha;
    }

    void Color::setRed(std::uint8_t red)
    {
        _red = red;
    }

    void Color::setGreen(std::uint8_t green)
    {
        _green = green;
    }

    void Color::setBlue(std::uint8_t blue)
    {
        _blue = blue;
    }

    void Color::setAlpha(std::uint8_t alpha)
    {
        _alpha = alpha;
    }
} // namespace GUI
