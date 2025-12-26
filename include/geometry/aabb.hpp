#pragma once
#include "../vectors/vector3.hpp"
#include "rect.hpp"
#include "../matrices/matrix4x4.hpp"
#include <array>
#include <algorithm>

template<typename T>
class AABB {
public:
    Vector3<T> min;
    Vector3<T> max;
    
    AABB();
    AABB(const Vector3<T>& min, const Vector3<T>& max);
    AABB(T minX, T minY, T minZ, T maxX, T maxY, T maxZ);
    
    static AABB fromPoints(const Vector3<T>& p1, const Vector3<T>& p2);
    static AABB fromCenterSize(const Vector3<T>& center, const Vector3<T>& size);
    
    Vector3<T> center() const;
    Vector3<T> size() const;
    Vector3<T> extents() const;
    T width() const;
    T height() const;
    T depth() const;
    
    bool contains(const Vector3<T>& point) const;
    bool contains(const AABB& other) const;
    bool intersects(const AABB& other) const;
    
    T volume() const;
    T surfaceArea() const;
    
    void expand(const Vector3<T>& point);
    void expand(const AABB& other);
    
    AABB transformed(const Matrix4x4<T>& transform) const;
    T distanceTo(const Vector3<T>& point) const;
    
    std::array<Vector3<T>, 8> getCorners() const;
    
    bool intersectRay(const Vector3<T>& origin, const Vector3<T>& direction,
                     T& tMin, T& tMax) const;
    bool intersectPlane(const Vector3<T>& planeNormal, T planeDistance) const;
    
    enum class PlaneIntersection {
        Front,
        Back,
        Intersecting
    };
    
    PlaneIntersection classifyPlane(const Vector3<T>& planeNormal, T planeDistance) const;
    
    static AABB merge(const AABB& a, const AABB& b);
    bool isEmpty() const;
};

using AABBf = AABB<float>;
using AABBi = AABB<int>;
