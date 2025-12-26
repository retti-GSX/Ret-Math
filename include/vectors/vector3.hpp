#pragma once
#include <cmath>

template<typename T>
struct Vector3 {
    T x, y, z;
    
    Vector3(T x = 0, T y = 0, T z = 0);
    
    Vector3 operator+(const Vector3& other) const;
    Vector3 operator-(const Vector3& other) const;
    Vector3 operator-() const;
    Vector3 operator*(T scalar) const;
    Vector3 operator/(T scalar) const;
    
    Vector3 cross(const Vector3& other) const;
    T dot(const Vector3& other) const;
    T length() const;
    T lengthSquared() const;
    Vector3 normalized() const;
    void normalize();
    
    Vector3 rotatedX(T angle) const;
    Vector3 rotatedY(T angle) const;
    Vector3 rotatedZ(T angle) const;

    bool equals(const Vector3& other, T epsilon = 1e-6f) const;

    static Vector3 lerp(const Vector3& a, const Vector3& b, T t);
};

using Vector3f = Vector3<float>;
using Vector3i = Vector3<int>;
