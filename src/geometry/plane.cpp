#include "../../include/geometry/plane.hpp"

// Constructors

template<typename T>
Plane<T>::Plane() : normal(Vector3<T>(0, 1, 0)), distance(0) {}

template<typename T>
Plane<T>::Plane(const Vector3<T>& normal, T distance) : normal(normal), distance(distance) {}

template<typename T>
Plane<T>::Plane(const Vector3<T>& point, const Vector3<T>& normal) : normal(normal), distance(-point.dot(normal)) {}

template<typename T>
Plane<T>::Plane(const Vector3<T>& a, const Vector3<T>& b, const Vector3<T>& c) {
    Vector3<T> ab = b - a;
    Vector3<T> ac = c - a;
    normal = ab.cross(ac).normalized();
    distance = -a.dot(normal);
}

// Getters

template<typename T>
Vector3<T> Plane<T>::getNormal() const { return normal; }

template<typename T>
T Plane<T>::getDistance() const { return distance; }

// Distance to point

template<typename T>
T Plane<T>::distanceToPoint(const Vector3<T>& point) const {
    return normal.dot(point) + distance;
}

// Ray intersection

template<typename T>
bool Plane<T>::intersectRay(const Vector3<T>& origin, const Vector3<T>& direction,
                           T& t, Vector3<T>& intersection) const {
    T denominator = normal.dot(direction);
    if (std::abs(denominator) < 1e-6f) {
        return false;
    }
    t = -(normal.dot(origin) + distance) / denominator;
    intersection = origin + direction * t;
    return true;
}

// Reflection

template<typename T>
Vector3<T> Plane<T>::reflect(const Vector3<T>& direction) const {
    return direction - normal * (2 * normal.dot(direction));
}

// Point projection

template<typename T>
Vector3<T> Plane<T>::projectPoint(const Vector3<T>& point) const {
    return point - normal * distanceToPoint(point);
}

// Normalization

template<typename T>
void Plane<T>::normalize() {
    T length = normal.length();
    if (length > 0) {
        normal = normal / length;
        distance = distance / length;
    }
}

template<typename T>
Plane<T> Plane<T>::normalized() const {
    Plane<T> result = *this;
    result.normalize();
    return result;
}

// Parallel check

template<typename T>
bool Plane<T>::isParallel(const Plane<T>& other, T epsilon) const {
    T dot = normal.dot(other.normal);
    return std::abs(dot) > (1 - epsilon);
}

// Equality check

template<typename T>
bool Plane<T>::equals(const Plane<T>& other, T epsilon) const {
    return normal.equals(other.normal, epsilon) &&
            std::abs(distance - other.distance) < epsilon;
}

// Explicit template instantiations
template class Plane<float>;
template class Plane<double>;