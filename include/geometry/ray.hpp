#pragma once
#include "../vectors/vector3.hpp"
#include "../matrices/matrix4x4.hpp"
#include <cmath>

template<typename T>
class Ray {
public:
    Vector3<T> origin;
    Vector3<T> direction;
    
    Ray(const Vector3<T>& origin = Vector3<T>(),
        const Vector3<T>& direction = Vector3<T>(0, 0, 1));
    
    // Point on ray at parameter t
    Vector3<T> pointAt(T t) const;
    
    // Plane intersection check
    bool intersectPlane(const Vector3<T>& planePoint, const Vector3<T>& planeNormal,
                       T& t, Vector3<T>& intersection) const;
    
    // Reflection from normal
    Ray reflect(const Vector3<T>& normal, const Vector3<T>& intersection) const;
    
    // Direction normalization
    void normalize();
    Ray normalized() const;
    
    // Get inverse ray
    Ray inverse() const;
    
    // Ray transformation
    Ray transformed(const Matrix4x4<T>& transform) const;
    
    // Equality check
    bool equals(const Ray& other, T epsilon = 1e-6f) const;
};

using Rayf = Ray<float>;
using Rayd = Ray<double>;