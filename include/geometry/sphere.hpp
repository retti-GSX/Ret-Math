#pragma once
#include "../vectors/vector3.hpp"

template<typename T>
class Sphere {
public:
    Vector3<T> center;
    T radius;
    
    Sphere();
    Sphere(const Vector3<T>& center, T radius);
    
    bool contains(const Vector3<T>& point) const;
    bool intersects(const Sphere& other) const;
    bool intersects(const Vector3<T>& point) const;
    
    T volume() const;
    T surfaceArea() const;
    
    bool intersectRay(const Vector3<T>& origin, const Vector3<T>& direction, T& t) const;
};

using Spheref = Sphere<float>;
using Spherei = Sphere<int>;