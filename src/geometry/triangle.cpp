#include "../../include/geometry/triangle.hpp"
#include "../../include/vectors/vector3.hpp"
#include <cmath>

template<typename T>
Triangle<T>::Triangle() : a(Vector3<T>(0, 0, 0)), b(Vector3<T>(0, 0, 0)), c(Vector3<T>(0, 0, 0)) {}

template<typename T>
Triangle<T>::Triangle(const Vector3<T>& a, const Vector3<T>& b, const Vector3<T>& c) 
    : a(a), b(b), c(c) {}

template<typename T>
Vector3<T> Triangle<T>::normal() const {
    Vector3<T> edge1 = b - a;
    Vector3<T> edge2 = c - a;
    return edge1.cross(edge2).normalized();
}

template<typename T>
T Triangle<T>::area() const {
    Vector3<T> edge1 = b - a;
    Vector3<T> edge2 = c - a;
    return edge1.cross(edge2).length() * 0.5;
}

template<typename T>
bool Triangle<T>::contains(const Vector3<T>& point) const {
    Vector3<T> bary = barycentric(point);
    return bary.x >= 0 && bary.y >= 0 && bary.z >= 0 && bary.x <= 1 && bary.y <= 1 && bary.z <= 1;
}

template<typename T>
Vector3<T> Triangle<T>::barycentric(const Vector3<T>& point) const {
    Vector3<T> v0 = b - a;
    Vector3<T> v1 = c - a;
    Vector3<T> v2 = point - a;
    
    T d00 = v0.dot(v0);
    T d01 = v0.dot(v1);
    T d11 = v1.dot(v1);
    T d20 = v2.dot(v0);
    T d21 = v2.dot(v1);
    
    T denom = d00 * d11 - d01 * d01;
    T v = (d11 * d20 - d01 * d21) / denom;
    T w = (d00 * d21 - d01 * d20) / denom;
    T u = 1.0 - v - w;
    
    return Vector3<T>(u, v, w);
}

template<typename T>
bool Triangle<T>::intersectRay(const Vector3<T>& origin, const Vector3<T>& direction, T& t) const {
    Vector3<T> edge1 = b - a;
    Vector3<T> edge2 = c - a;
    Vector3<T> h = direction.cross(edge2);
    T a = edge1.dot(h);
    
    if (a > -static_cast<T>(1e-6) && a < static_cast<T>(1e-6)) {
        return false; // Ray is parallel to triangle
    }
    
    T f = 1.0 / a;
    Vector3<T> s = origin - a;
    T u = f * s.dot(h);
    
    if (u < 0.0 || u > 1.0) {
        return false;
    }
    
    Vector3<T> q = s.cross(edge1);
    T v = f * direction.dot(q);
    
    if (v < 0.0 || u + v > 1.0) {
        return false;
    }
    
    t = f * edge2.dot(q);
    
    return t > static_cast<T>(1e-6);
}

// Explicit instantiations
template class Triangle<float>;
template class Triangle<int>;