#pragma once
#include "../vectors/vector3.hpp"

template<typename T>
class Triangle {
public:
    Vector3<T> a;
    Vector3<T> b;
    Vector3<T> c;
    
    Triangle();
    Triangle(const Vector3<T>& a, const Vector3<T>& b, const Vector3<T>& c);
    
    Vector3<T> normal() const;
    T area() const;
    
    bool contains(const Vector3<T>& point) const;
    
    Vector3<T> barycentric(const Vector3<T>& point) const;
    
    bool intersectRay(const Vector3<T>& origin, const Vector3<T>& direction, T& t) const;
};

using Trianglef = Triangle<float>;
using Trianglei = Triangle<int>;