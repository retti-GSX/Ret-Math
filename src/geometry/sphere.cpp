#include "../../include/geometry/sphere.hpp"
#include "../../include/vectors/vector3.hpp"
#include <cmath>

template<typename T>
Sphere<T>::Sphere() : center(Vector3<T>(0, 0, 0)), radius(0) {}

template<typename T>
Sphere<T>::Sphere(const Vector3<T>& center, T radius) : center(center), radius(radius) {}

template<typename T>
bool Sphere<T>::contains(const Vector3<T>& point) const {
    return (point - center).lengthSquared() <= radius * radius;
}

template<typename T>
bool Sphere<T>::intersects(const Sphere& other) const {
    T distanceSquared = (center - other.center).lengthSquared();
    T radiusSum = radius + other.radius;
    return distanceSquared <= radiusSum * radiusSum;
}

template<typename T>
bool Sphere<T>::intersects(const Vector3<T>& point) const {
    return contains(point);
}

template<typename T>
T Sphere<T>::volume() const {
    return (4.0 / 3.0) * static_cast<T>(3.14159265358979323846) * radius * radius * radius;
}

template<typename T>
T Sphere<T>::surfaceArea() const {
    return 4.0 * static_cast<T>(3.14159265358979323846) * radius * radius;
}

template<typename T>
bool Sphere<T>::intersectRay(const Vector3<T>& origin, const Vector3<T>& direction, T& t) const {
    Vector3<T> oc = origin - center;
    T a = direction.dot(direction);
    T b = 2.0 * oc.dot(direction);
    T c = oc.dot(oc) - radius * radius;
    T discriminant = b * b - 4.0 * a * c;
    
    if (discriminant < 0) {
        return false;
    }
    
    T sqrtDiscriminant = std::sqrt(discriminant);
    T t0 = (-b - sqrtDiscriminant) / (2.0 * a);
    T t1 = (-b + sqrtDiscriminant) / (2.0 * a);
    
    if (t0 >= 0) {
        t = t0;
        return true;
    } else if (t1 >= 0) {
        t = t1;
        return true;
    }
    
    return false;
}

// Explicit instantiations
template class Sphere<float>;
template class Sphere<int>;