#include "../../include/geometry/capsule.hpp"
#include "../../include/vectors/vector3.hpp"
#include <cmath>
#include <algorithm>

template<typename T>
Capsule<T>::Capsule() : start(Vector3<T>(0, 0, 0)), end(Vector3<T>(0, 0, 0)), radius(0) {}

template<typename T>
Capsule<T>::Capsule(const Vector3<T>& start, const Vector3<T>& end, T radius) 
    : start(start), end(end), radius(radius) {}

template<typename T>
bool Capsule<T>::contains(const Vector3<T>& point) const {
    Vector3<T> line = end - start;
    Vector3<T> pointToStart = point - start;
    
    T lineLengthSquared = line.lengthSquared();
    T projection = pointToStart.dot(line) / lineLengthSquared;
    
    projection = std::max(static_cast<T>(0), std::min(static_cast<T>(1), projection));
    
    Vector3<T> closestPoint = start + line * projection;
    
    return (point - closestPoint).lengthSquared() <= radius * radius;
}

template<typename T>
bool Capsule<T>::intersects(const Capsule& other) const {
    // Simplified intersection check
    return false;
}

template<typename T>
T Capsule<T>::length() const {
    return (end - start).length();
}

template<typename T>
Vector3<T> Capsule<T>::center() const {
    return (start + end) * 0.5;
}

template<typename T>
bool Capsule<T>::intersectRay(const Vector3<T>& origin, const Vector3<T>& direction, T& t) const {
    // Simplified ray intersection
    return false;
}

// Explicit instantiations
template class Capsule<float>;
template class Capsule<int>;