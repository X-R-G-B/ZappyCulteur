/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** Vector3F
*/

#pragma once

namespace GUI {
    class Vector3F {
        public:
            Vector3F(float x = 0, float y = 0, float z = 0);
            ~Vector3F() = default;
            float x;
            float y;
            float z;
            Vector3F operator+(const Vector3F &vector) const;
            Vector3F operator-(const Vector3F &vector) const;
            Vector3F operator*(const Vector3F &vector) const;
            Vector3F operator/(const Vector3F &vector) const;
            Vector3F operator*(float value) const;
            Vector3F operator/(float value) const;
            Vector3F operator-(float value) const;
            Vector3F operator+(float value) const;
            Vector3F &operator+=(const Vector3F &vector);
            Vector3F &operator-=(const Vector3F &vector);
            Vector3F &operator*=(const Vector3F &vector);
            Vector3F &operator/=(const Vector3F &vector);
            Vector3F &operator*=(float value);
            Vector3F &operator/=(float value);
            Vector3F &operator-=(float value);
            Vector3F &operator+=(float value);
            bool operator==(const Vector3F &vector) const;
            bool operator!=(const Vector3F &vector) const;
    };
} // namespace GUI
