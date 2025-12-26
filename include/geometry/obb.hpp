#pragma once
#include "../vectors/vector3.hpp"
#include "../matrices/matrix4x4.hpp"

template<typename T>
class OBB {
public:
    Vector3<T> center;
    Vector3<T> extents;
    Vector3<T> axes[3];
    
    OBB();
    OBB(const Vector3<T>& center, const Vector3<T>& extents, const Vector3<T>& xAxis, 
        const Vector3<T>& yAxis, const Vector3<T>& zAxis);
    
    bool contains(const Vector3<T>& point) const;
    bool intersects(const OBB& other) const;
    
    T volume() const;
    T surfaceArea() const;
    
    bool intersectRay(const Vector3<T>& origin, const Vector3<T>& direction, T& tMin, T& tMax) const;
    
    OBB transformed(const Matrix4x4<T>& transform) const;
private:
    Vector3<T> getCorner(int index) const;
};

using OBBf = OBB<float>;
using OBBi = OBB<int>;