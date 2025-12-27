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
    
    // Model matrix (model space -> world space)
    Matrix4x4<T> getModelMatrix() const {
        return buildModelMatrix(position, rotation, scale);
    }
    Matrix4x4<T> getInverseModelMatrix() const { 
        Matrix4x4<T> translationMat = Matrix4x4<T>::translation(-position);
        Matrix4x4<T> rotationMat = rotation.inverse().toMatrix();
        Matrix4x4<T> scaleMat = Matrix4x4<T>::scaling(Vector3<T>(1/scale.x, 1/scale.y, 1/scale.z));
        return scaleMat * rotationMat * translationMat;
    }
    
    // Legacy aliases for compatibility
    Matrix4x4<T> getMatrix() const { return getModelMatrix(); }
    Matrix4x4<T> getInverseMatrix() const { return getInverseModelMatrix(); }
    
    // Point and vector transformations
    Vector3<T> transformPoint(const Vector3<T>& point) const {     // Model space -> World space
        return getModelMatrix().transformPoint(point);
    }
    Vector3<T> transformVector(const Vector3<T>& vector) const {   // Direction vectors (no translation)
        return rotation.rotate(vector) * scale; // Apply rotation and scale only
    }
    Vector3<T> inverseTransformPoint(const Vector3<T>& point) const { // World space -> Model space
        return getInverseModelMatrix().transformPoint(point);
    }
    
    // Space transformation helpers
    static Matrix4x4<T> buildModelMatrix(const Vector3<T>& position, 
                                        const Quaternion<T>& rotation, 
                                        const Vector3<T>& scale) {
        Matrix4x4<T> translationMat = Matrix4x4<T>::translation(position);
        Matrix4x4<T> rotationMat = rotation.toMatrix();
        Matrix4x4<T> scaleMat = Matrix4x4<T>::scaling(scale);
        return translationMat * rotationMat * scaleMat;
    }
    
    static Transform fromModelMatrix(const Matrix4x4<T>& matrix);
    
    // Transformation decomposition
    void decomposeModelMatrix(const Matrix4x4<T>& matrix);
    
    // Combining transformations (parent * child)
    Transform combine(const Transform& child) const;
    
    // Interpolation
    static Transform lerp(const Transform& a, const Transform& b, T t);
    static Transform slerp(const Transform& a, const Transform& b, T t); // Spherical interpolation
    
    // Getters and setters
    void setPosition(const Vector3<T>& pos);
    void setRotation(const Quaternion<T>& rot);
    void setScale(const Vector3<T>& scl);
    
    Vector3<T> getPosition() const;
    Quaternion<T> getRotation() const;
    Vector3<T> getScale() const;
    
    // Local transformations (relative to current transform)
    void translate(const Vector3<T>& translation);
    void rotate(const Quaternion<T>& rot);
    void scaleBy(const Vector3<T>& scaling);
    
    // Transform directions
    Vector3<T> forward() const;   // Local Z+ direction in world space
    Vector3<T> up() const;        // Local Y+ direction in world space
    Vector3<T> right() const;     // Local X+ direction in world space
};
