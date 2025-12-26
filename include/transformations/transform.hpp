#pragma once
#include "../vectors/vector3.hpp"
#include "../quaternions/quaternion.hpp"
#include "../matrices/matrix4x4.hpp"

template<typename T>
class Transform {
private:
    Vector3<T> position;
    Quaternion<T> rotation;
    Vector3<T> scale;
    
public:
    Transform();
    Transform(const Vector3<T>& pos, const Quaternion<T>& rot, const Vector3<T>& scl);
    
    // Transformation matrix
    Matrix4x4<T> getMatrix() const;
    Matrix4x4<T> getInverseMatrix() const;
    
    // Point and vector transformations
    Vector3<T> transformPoint(const Vector3<T>& point) const;
    Vector3<T> transformVector(const Vector3<T>& vector) const;
    
    // Combining transformations
    Transform combine(const Transform& other) const;
    
    // Interpolation
    static Transform lerp(const Transform& a, const Transform& b, T t);
    
    // Getters and setters
    void setPosition(const Vector3<T>& pos);
    void setRotation(const Quaternion<T>& rot);
    void setScale(const Vector3<T>& scl);
    
    Vector3<T> getPosition() const;
    Quaternion<T> getRotation() const;
    Vector3<T> getScale() const;
    
    // Local transformations
    void translate(const Vector3<T>& translation);
    void rotate(const Quaternion<T>& rot);
    void scaleBy(const Vector3<T>& scaling);
};
