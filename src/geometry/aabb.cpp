#include "../../include/geometry/aabb.hpp"

// Constructors

template<typename T>
AABB<T>::AABB() : min(Vector3<T>(0, 0, 0)), max(Vector3<T>(0, 0, 0)) {}

template<typename T>
AABB<T>::AABB(const Vector3<T>& min, const Vector3<T>& max) : min(min), max(max) {}

template<typename T>
AABB<T>::AABB(T minX, T minY, T minZ, T maxX, T maxY, T maxZ) : min(Vector3<T>(minX, minY, minZ)), max(Vector3<T>(maxX, maxY, maxZ)) {}

// Static methods

template<typename T>
AABB<T> AABB<T>::fromPoints(const Vector3<T>& p1, const Vector3<T>& p2) {
    return AABB<T>(
        Vector3<T>(std::min(p1.x, p2.x), std::min(p1.y, p2.y), std::min(p1.z, p2.z)),
        Vector3<T>(std::max(p1.x, p2.x), std::max(p1.y, p2.y), std::max(p1.z, p2.z))
    );
}

template<typename T>
AABB<T> AABB<T>::fromCenterSize(const Vector3<T>& center, const Vector3<T>& size) {
    return AABB<T>(center - size / 2, center + size / 2);
}

// Properties

template<typename T>
Vector3<T> AABB<T>::center() const {
    return (min + max) / 2;
}

template<typename T>
Vector3<T> AABB<T>::size() const {
    return max - min;
}

template<typename T>
Vector3<T> AABB<T>::extents() const {
    return size() / 2;
}

template<typename T>
T AABB<T>::width() const {
    return max.x - min.x;
}

template<typename T>
T AABB<T>::height() const {
    return max.y - min.y;
}

template<typename T>
T AABB<T>::depth() const {
    return max.z - min.z;
}

// Containment and intersection

template<typename T>
bool AABB<T>::contains(const Vector3<T>& point) const {
    return point.x >= min.x && point.x <= max.x &&
           point.y >= min.y && point.y <= max.y &&
           point.z >= min.z && point.z <= max.z;
}

template<typename T>
bool AABB<T>::contains(const AABB<T>& other) const {
    return other.min.x >= min.x && other.max.x <= max.x &&
           other.min.y >= min.y && other.max.y <= max.y &&
           other.min.z >= min.z && other.max.z <= max.z;
}

template<typename T>
bool AABB<T>::intersects(const AABB<T>& other) const {
    return !(other.max.x < min.x || other.min.x > max.x ||
             other.max.y < min.y || other.min.y > max.y ||
             other.max.z < min.z || other.min.z > max.z);
}

// Volume and area

template<typename T>
T AABB<T>::volume() const {
    Vector3<T> s = size();
    return s.x * s.y * s.z;
}

template<typename T>
T AABB<T>::surfaceArea() const {
    Vector3<T> s = size();
    return 2 * (s.x * s.y + s.x * s.z + s.y * s.z);
}

// Expansion

template<typename T>
void AABB<T>::expand(const Vector3<T>& point) {
    min.x = std::min(min.x, point.x);
    min.y = std::min(min.y, point.y);
    min.z = std::min(min.z, point.z);
    max.x = std::max(max.x, point.x);
    max.y = std::max(max.y, point.y);
    max.z = std::max(max.z, point.z);
}

template<typename T>
void AABB<T>::expand(const AABB<T>& other) {
    min.x = std::min(min.x, other.min.x);
    min.y = std::min(min.y, other.min.y);
    min.z = std::min(min.z, other.min.z);
    max.x = std::max(max.x, other.max.x);
    max.y = std::max(max.y, other.max.y);
    max.z = std::max(max.z, other.max.z);
}

// Transformations

template<typename T>
AABB<T> AABB<T>::transformed(const Matrix4x4<T>& transform) const {
    std::array<Vector3<T>, 8> corners = getCorners();
    AABB<T> result;
    for (const auto& corner : corners) {
        result.expand(transform.transformPoint(corner));
    }
    return result;
}

template<typename T>
T AABB<T>::distanceTo(const Vector3<T>& point) const {
    T dx = std::max(std::max(min.x - point.x, point.x - max.x), static_cast<T>(0));
    T dy = std::max(std::max(min.y - point.y, point.y - max.y), static_cast<T>(0));
    T dz = std::max(std::max(min.z - point.z, point.z - max.z), static_cast<T>(0));
    return std::sqrt(dx * dx + dy * dy + dz * dz);
}

// Corners

template<typename T>
std::array<Vector3<T>, 8> AABB<T>::getCorners() const {
    return {
        Vector3<T>(min.x, min.y, min.z),
        Vector3<T>(max.x, min.y, min.z),
        Vector3<T>(min.x, max.y, min.z),
        Vector3<T>(max.x, max.y, min.z),
        Vector3<T>(min.x, min.y, max.z),
        Vector3<T>(max.x, min.y, max.z),
        Vector3<T>(min.x, max.y, max.z),
        Vector3<T>(max.x, max.y, max.z)
    };
}

// Ray intersection

template<typename T>
bool AABB<T>::intersectRay(const Vector3<T>& origin, const Vector3<T>& direction,
                          T& tMin, T& tMax) const {
    T t1 = (min.x - origin.x) / direction.x;
    T t2 = (max.x - origin.x) / direction.x;
    T t3 = (min.y - origin.y) / direction.y;
    T t4 = (max.y - origin.y) / direction.y;
    T t5 = (min.z - origin.z) / direction.z;
    T t6 = (max.z - origin.z) / direction.z;
    
    tMin = std::max(std::max(std::min(t1, t2), std::min(t3, t4)), std::min(t5, t6));
    tMax = std::min(std::min(std::max(t1, t2), std::max(t3, t4)), std::max(t5, t6));
    
    return tMax > 0 && tMin < tMax;
}

// Plane intersection

template<typename T>
bool AABB<T>::intersectPlane(const Vector3<T>& planeNormal, T planeDistance) const {
    T minDist = planeNormal.dot(min) + planeDistance;
    T maxDist = planeNormal.dot(max) + planeDistance;
    return (minDist <= 0 && maxDist >= 0) || (minDist >= 0 && maxDist <= 0);
}

template<typename T>
typename AABB<T>::PlaneIntersection AABB<T>::classifyPlane(const Vector3<T>& planeNormal, T planeDistance) const {
    T minDist = planeNormal.dot(min) + planeDistance;
    T maxDist = planeNormal.dot(max) + planeDistance;
    
    if (minDist > 0) return PlaneIntersection::Front;
    if (maxDist < 0) return PlaneIntersection::Back;
    return PlaneIntersection::Intersecting;
}

// Merging

template<typename T>
AABB<T> AABB<T>::merge(const AABB<T>& a, const AABB<T>& b) {
    return AABB<T>(
        Vector3<T>(std::min(a.min.x, b.min.x), std::min(a.min.y, b.min.y), std::min(a.min.z, b.min.z)),
        Vector3<T>(std::max(a.max.x, b.max.x), std::max(a.max.y, b.max.y), std::max(a.max.z, b.max.z))
    );
}

// Empty check

template<typename T>
bool AABB<T>::isEmpty() const {
    return min.x >= max.x || min.y >= max.y || min.z >= max.z;
}

// Explicit template instantiations
template class AABB<float>;
template class AABB<int>;
