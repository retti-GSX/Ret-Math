#include "../../include/geometry/obb.hpp"
#include "../../include/vectors/vector3.hpp"
#include "../../include/matrices/matrix4x4.hpp"
#include <cmath>
#include <algorithm>

template<typename T>
OBB<T>::OBB() : center(Vector3<T>(0, 0, 0)), extents(Vector3<T>(0, 0, 0)) {
    axes[0] = Vector3<T>(1, 0, 0);
    axes[1] = Vector3<T>(0, 1, 0);
    axes[2] = Vector3<T>(0, 0, 1);
}

template<typename T>
OBB<T>::OBB(const Vector3<T>& center, const Vector3<T>& extents, 
             const Vector3<T>& xAxis, const Vector3<T>& yAxis, const Vector3<T>& zAxis)
    : center(center), extents(extents) {
    axes[0] = xAxis.normalized();
    axes[1] = yAxis.normalized();
    axes[2] = zAxis.normalized();
}

template<typename T>
bool OBB<T>::contains(const Vector3<T>& point) const {
    Vector3<T> localPoint = point - center;
    
    T distanceX = localPoint.dot(axes[0]);
    T distanceY = localPoint.dot(axes[1]);
    T distanceZ = localPoint.dot(axes[2]);
    
    if (distanceX < -extents.x || distanceX > extents.x ||
        distanceY < -extents.y || distanceY > extents.y ||
        distanceZ < -extents.z || distanceZ > extents.z) {
        return false;
    }
    
    return true;
}

template<typename T>
bool OBB<T>::intersects(const OBB& other) const {
    // Separating Axis Theorem
    Vector3<T> axesToTest[15];
    
    // Add axes from this OBB
    for (int i = 0; i < 3; ++i) {
        axesToTest[i] = axes[i];
    }
    
    // Add axes from other OBB
    for (int i = 0; i < 3; ++i) {
        axesToTest[3 + i] = other.axes[i];
    }
    
    // Add cross products of axes
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            axesToTest[6 + i * 3 + j] = axes[i].cross(other.axes[j]);
        }
    }
    
    for (int i = 0; i < 15; ++i) {
        Vector3<T> axis = axesToTest[i];
        if (axis.lengthSquared() < static_cast<T>(1e-6)) {
            continue;
        }
        
        axis = axis.normalized();
        
        T min1 = static_cast<T>(INFINITY);
        T max1 = static_cast<T>(-INFINITY);
        T min2 = static_cast<T>(INFINITY);
        T max2 = static_cast<T>(-INFINITY);
        
        // Project this OBB onto axis
        for (int j = 0; j < 8; ++j) {
            Vector3<T> corner = getCorner(j);
            T projection = corner.dot(axis);
            
            if (projection < min1) min1 = projection;
            if (projection > max1) max1 = projection;
        }
        
        // Project other OBB onto axis
        for (int j = 0; j < 8; ++j) {
            Vector3<T> corner = other.getCorner(j);
            T projection = corner.dot(axis);
            
            if (projection < min2) min2 = projection;
            if (projection > max2) max2 = projection;
        }
        
        if (max1 < min2 || max2 < min1) {
            return false;
        }
    }
    
    return true;
}

template<typename T>
Vector3<T> OBB<T>::getCorner(int index) const {
    T signX = (index & 1) ? static_cast<T>(1) : static_cast<T>(-1);
    T signY = (index & 2) ? static_cast<T>(1) : static_cast<T>(-1);
    T signZ = (index & 4) ? static_cast<T>(1) : static_cast<T>(-1);
    
    Vector3<T> corner = axes[0] * extents.x * signX +
                        axes[1] * extents.y * signY +
                        axes[2] * extents.z * signZ;
    
    return center + corner;
}

template<typename T>
T OBB<T>::volume() const {
    return 8.0 * extents.x * extents.y * extents.z;
}

template<typename T>
T OBB<T>::surfaceArea() const {
    return 8.0 * (extents.x * extents.y + extents.y * extents.z + extents.z * extents.x);
}

template<typename T>
bool OBB<T>::intersectRay(const Vector3<T>& origin, const Vector3<T>& direction, T& tMin, T& tMax) const {
    // Simplified ray intersection
    return false;
}

template<typename T>
OBB<T> OBB<T>::transformed(const Matrix4x4<T>& transform) const {
    Vector3<T> newCenter = transform.transformPoint(center);
    Vector3<T> newExtents = extents;
    
    Vector3<T> newAxes[3];
    for (int i = 0; i < 3; ++i) {
        newAxes[i] = transform.transformVector(axes[i]);
    }
    
    return OBB<T>(newCenter, newExtents, newAxes[0], newAxes[1], newAxes[2]);
}

// Explicit instantiations
template class OBB<float>;
template class OBB<int>;