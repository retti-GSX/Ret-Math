#pragma once
#include "../vectors/vector3.hpp"
#include "../matrices/matrix4x4.hpp"
#include <cmath>

template<typename T>
class Quaternion {
private:
    T w, x, y, z;
    
public:
    Quaternion(T w = 1, T x = 0, T y = 0, T z = 0);
    Quaternion(const Vector3<T>& axis, T angle);
    
    // Normalization
    Quaternion normalized() const;
    void normalize();
    
    // Inverse quaternion
    Quaternion conjugate() const;
    Quaternion inverse() const;
    
    // Multiplication
    Quaternion operator*(const Quaternion& other) const;
    Vector3<T> operator*(const Vector3<T>& vec) const;
    
    // Linear interpolation
    static Quaternion lerp(const Quaternion& a, const Quaternion& b, T t);
    static Quaternion slerp(const Quaternion& a, const Quaternion& b, T t);
    
    // Transformations
    Matrix4x4<T> toMatrix() const;
    static Quaternion fromMatrix(const Matrix4x4<T>& mat);
    
    // Axis and angle
    void toAxisAngle(Vector3<T>& axis, T& angle) const;
    static Quaternion fromAxisAngle(const Vector3<T>& axis, T angle);
    
    // Euler angles
    static Quaternion fromEuler(T pitch, T yaw, T roll);
    Vector3<T> toEuler() const;
};
