/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** Vector3F
*/

#include "Vector3F.hpp"

namespace GUI {
    Vector3F::Vector3F(float x, float y, float z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    Vector3F Vector3F::operator+(const Vector3F &vector) const
    {
        return Vector3F(this->x + vector.x, this->y + vector.y, this->z + vector.z);
    }

    Vector3F Vector3F::operator-(const Vector3F &vector) const
    {
        return Vector3F(this->x - vector.x, this->y - vector.y, this->z - vector.z);
    }

    Vector3F Vector3F::operator*(const Vector3F &vector) const
    {
        return Vector3F(this->x * vector.x, this->y * vector.y, this->z * vector.z);
    }

    Vector3F Vector3F::operator/(const Vector3F &vector) const
    {
        return Vector3F(this->x / vector.x, this->y / vector.y, this->z / vector.z);
    }

    Vector3F &Vector3F::operator+=(const Vector3F &vector)
    {
        this->x += vector.x;
        this->y += vector.y;
        this->z += vector.z;
        return *this;
    }

    Vector3F &Vector3F::operator-=(const Vector3F &vector)
    {
        this->x -= vector.x;
        this->y -= vector.y;
        this->z -= vector.z;
        return *this;
    }

    Vector3F &Vector3F::operator*=(const Vector3F &vector)
    {
        this->x *= vector.x;
        this->y *= vector.y;
        this->z *= vector.z;
        return *this;
    }

    Vector3F &Vector3F::operator/=(const Vector3F &vector)
    {
        this->x /= vector.x;
        this->y /= vector.y;
        this->z /= vector.z;
        return *this;
    }

    bool Vector3F::operator==(const Vector3F &vector) const
    {
        return this->x == vector.x && this->y == vector.y && this->z == vector.z;
    }

    bool Vector3F::operator!=(const Vector3F &vector) const
    {
        return this->x != vector.x || this->y != vector.y || this->z != vector.z;
    }

    Vector3F Vector3F::operator*(float value) const
    {
        return Vector3F(this->x * value, this->y * value, this->z * value);
    }

    Vector3F Vector3F::operator/(float value) const
    {
        return Vector3F(this->x / value, this->y / value, this->z / value);
    }
}
