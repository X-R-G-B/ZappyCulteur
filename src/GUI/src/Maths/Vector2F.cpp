/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** Vector2F
*/

#include "Vector2F.hpp"

namespace GUI {
    Vector2F::Vector2F(float x, float y)
    {
        this->x = x;
        this->y = y;
    }

    Vector2F Vector2F::operator+(const Vector2F &vector) const
    {
        return Vector2F(this->x + vector.x, this->y + vector.y);
    }

    Vector2F Vector2F::operator-(const Vector2F &vector) const
    {
        return Vector2F(this->x - vector.x, this->y - vector.y);
    }

    Vector2F Vector2F::operator*(const Vector2F &vector) const
    {
        return Vector2F(this->x * vector.x, this->y * vector.y);
    }

    Vector2F Vector2F::operator/(const Vector2F &vector) const
    {
        return Vector2F(this->x / vector.x, this->y / vector.y);
    }

    Vector2F &Vector2F::operator+=(const Vector2F &vector)
    {
        this->x += vector.x;
        this->y += vector.y;
        return *this;
    }

    Vector2F &Vector2F::operator-=(const Vector2F &vector)
    {
        this->x -= vector.x;
        this->y -= vector.y;
        return *this;
    }

    Vector2F &Vector2F::operator*=(const Vector2F &vector)
    {
        this->x *= vector.x;
        this->y *= vector.y;
        return *this;
    }

    Vector2F &Vector2F::operator/=(const Vector2F &vector)
    {
        this->x /= vector.x;
        this->y /= vector.y;
        return *this;
    }

    bool Vector2F::operator==(const Vector2F &vector) const
    {
        return (this->x == vector.x && this->y == vector.y);
    }

    bool Vector2F::operator!=(const Vector2F &vector) const
    {
        return (this->x != vector.x || this->y != vector.y);
    }

    Vector2F Vector2F::operator*(float value) const
    {
        return Vector2F(this->x * value, this->y * value);
    }

    Vector2F Vector2F::operator/(float value) const
    {
        return Vector2F(this->x / value, this->y / value);
    }

    Vector2F &Vector2F::operator*=(float value)
    {
        this->x *= value;
        this->y *= value;
        return *this;
    }

    Vector2F &Vector2F::operator/=(float value)
    {
        this->x /= value;
        this->y /= value;
        return *this;
    }

    Vector2F Vector2F::operator-(float value) const
    {
        return Vector2F(this->x - value, this->y - value);
    }

    Vector2F Vector2F::operator+(float value) const
    {
        return Vector2F(this->x + value, this->y + value);
    }

    Vector2F &Vector2F::operator-=(float value)
    {
        this->x -= value;
        this->y -= value;
        return *this;
    }

    Vector2F &Vector2F::operator+=(float value)
    {
        this->x += value;
        this->y += value;
        return *this;
    }
}

size_t std::hash<GUI::Vector2F>::operator()(const GUI::Vector2F& vector) const {
    size_t hashX = hash<float>{}(vector.x);
    size_t hashY = hash<float>{}(vector.y);
    return hashX ^ (hashY << 1);
}

bool std::equal_to<GUI::Vector2F>::operator()(const GUI::Vector2F& lhs, const GUI::Vector2F& rhs) const {
    return lhs.x == rhs.x && lhs.y == rhs.y;
}
