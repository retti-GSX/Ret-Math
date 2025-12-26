#pragma once
#include "../vectors/vector3.hpp"

template<typename T>
class Capsule {
public:
    Vector3<T> start;
    Vector3<T> end;
    T radius;
    
    Capsule();
    Capsule(const Vector3<T>& start, const Vector3<T>& end, T radius);
    
    bool contains(const Vector3<T>& point) const;
    bool intersects(const Capsule& other) const;
    
    T length() const;
    Vector3<T> center() const;
    
    bool intersectRay(const Vector3<T>& origin, const Vector3<T>& direction, T& t) const;
};

using Capsulef = Capsule<float>;
using Capsulei = Capsule<int>;