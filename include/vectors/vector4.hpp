#pragma once
#include <cmath>
#include "vector3.hpp"

template<typename T>
struct Vector4 {
    T x, y, z, w;
    
    Vector4(T x = 0, T y = 0, T z = 0, T w = 1);
    Vector4(const Vector3<T>& vec3, T w = 1);
    
    Vector4 operator+(const Vector4& other) const;
    Vector4 operator-(const Vector4& other) const;
    Vector4 operator*(T scalar) const;
    Vector4 operator/(T scalar) const;
    
    Vector3<T> xyz() const;
    Vector3<T> homogeneous() const;
    
    static Vector4 fromRGBA(T r, T g, T b, T a);
};

using Vector4f = Vector4<float>;
using Vector4i = Vector4<int>;
