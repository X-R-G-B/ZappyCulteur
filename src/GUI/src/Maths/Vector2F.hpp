/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** Vector2F
*/

#pragma once

namespace GUI {
    class Vector2F {
        public:
            Vector2F(float x = 0, float y = 0);
            ~Vector2F() = default;
            float x;
            float y;
            Vector2F operator+(const Vector2F &vector) const;
            Vector2F operator-(const Vector2F &vector) const;
            Vector2F operator*(const Vector2F &vector) const;
            Vector2F operator/(const Vector2F &vector) const;
            Vector2F operator*(float value) const;
            Vector2F operator/(float value) const;
            Vector2F operator-(float value) const;
            Vector2F operator+(float value) const;
            Vector2F &operator+=(const Vector2F &vector);
            Vector2F &operator-=(const Vector2F &vector);
            Vector2F &operator*=(const Vector2F &vector);
            Vector2F &operator/=(const Vector2F &vector);
            Vector2F &operator*=(float value);
            Vector2F &operator/=(float value);
            Vector2F &operator-=(float value);
            Vector2F &operator+=(float value);
            bool operator==(const Vector2F &vector) const;
            bool operator!=(const Vector2F &vector) const;
    };
}
