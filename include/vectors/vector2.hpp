#pragma once
#include <cmath>

template<typename T>
struct Vector2 {
    T x, y;
    
    Vector2(T x = 0, T y = 0);
    
    Vector2 operator+(const Vector2& other) const;
    Vector2 operator-(const Vector2& other) const;
    Vector2 operator*(T scalar) const;
    Vector2 operator/(T scalar) const;
    
    T length() const;
    T lengthSquared() const;
    Vector2 normalized() const;
    void normalize();
    T dot(const Vector2& other) const;
    T cross(const Vector2& other) const;
    
    static Vector2 lerp(const Vector2& a, const Vector2& b, T t);
};

using Vector2f = Vector2<float>;
using Vector2i = Vector2<int>;
