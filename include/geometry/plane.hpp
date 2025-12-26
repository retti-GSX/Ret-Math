#pragma once
#include "../vectors/vector3.hpp"
#include <cmath>

template<typename T>
class Plane {
private:
    Vector3<T> normal;
    T distance;
    
public:
    Plane();
    Plane(const Vector3<T>& normal, T distance);
    Plane(const Vector3<T>& point, const Vector3<T>& normal);
    Plane(const Vector3<T>& a, const Vector3<T>& b, const Vector3<T>& c);
    
    // Getters
    Vector3<T> getNormal() const;
    T getDistance() const;
    
    // Distance to point
    T distanceToPoint(const Vector3<T>& point) const;
    
    // Ray intersection
    bool intersectRay(const Vector3<T>& origin, const Vector3<T>& direction,
                     T& t, Vector3<T>& intersection) const;
    
    // Vector reflection
    Vector3<T> reflect(const Vector3<T>& direction) const;
    
    // Point projection on plane
    Vector3<T> projectPoint(const Vector3<T>& point) const;
    
    // Plane normalization
    void normalize();
    Plane normalized() const;
    
    // Parallel check
    bool isParallel(const Plane<T>& other, T epsilon = 1e-6f) const;
    
    // Equality check
    bool equals(const Plane<T>& other, T epsilon = 1e-6f) const;
};

using Planef = Plane<float>;
using Planed = Plane<double>;