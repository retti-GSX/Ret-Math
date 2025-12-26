#include "../../include/geometry/ray.hpp"

// Constructor

template<typename T>
Ray<T>::Ray(const Vector3<T>& origin, const Vector3<T>& direction) : origin(origin), direction(direction) {}

// Point at parameter t

template<typename T>
Vector3<T> Ray<T>::pointAt(T t) const {
    return origin + direction * t;
}

// Plane intersection

template<typename T>
bool Ray<T>::intersectPlane(const Vector3<T>& planePoint, const Vector3<T>& planeNormal,
                           T& t, Vector3<T>& intersection) const {
    T denominator = direction.dot(planeNormal);
    if (std::abs(denominator) < 1e-6f) {
        return false;
    }
    Vector3<T> toPlane = planePoint - origin;
    t = toPlane.dot(planeNormal) / denominator;
    intersection = origin + direction * t;
    return true;
}

// Reflection

template<typename T>
Ray<T> Ray<T>::reflect(const Vector3<T>& normal, const Vector3<T>& intersection) const {
    Vector3<T> reflectedDir = direction - normal * (2 * normal.dot(direction));
    return Ray<T>(intersection, reflectedDir);
}

// Normalization

template<typename T>
void Ray<T>::normalize() {
    direction.normalize();
}

template<typename T>
Ray<T> Ray<T>::normalized() const {
    Ray<T> result = *this;
    result.normalize();
    return result;
}

// Inverse ray

template<typename T>
Ray<T> Ray<T>::inverse() const {
    return Ray<T>(origin, -direction);
}

// Transformation

template<typename T>
Ray<T> Ray<T>::transformed(const Matrix4x4<T>& transform) const {
    Vector3<T> newOrigin = transform.transformPoint(origin);
    Vector3<T> newDirection = transform.transformVector(direction);
    return Ray<T>(newOrigin, newDirection);
}

// Equality check

template<typename T>
bool Ray<T>::equals(const Ray<T>& other, T epsilon) const {
    return origin.equals(other.origin, epsilon) &&
            direction.equals(other.direction, epsilon);
}

// Explicit template instantiations
template class Ray<float>;
template class Ray<double>;