#include "../../include/transformations/transform.hpp"

// Constructors

template<typename T>
Transform<T>::Transform() : position(Vector3<T>()), rotation(Quaternion<T>()), scale(Vector3<T>(1, 1, 1)) {}

template<typename T>
Transform<T>::Transform(const Vector3<T>& pos, const Quaternion<T>& rot, const Vector3<T>& scl)
    : position(pos), rotation(rot), scale(scl) {}

// Matrix methods

template<typename T>
Matrix4x4<T> Transform<T>::getMatrix() const {
    Matrix4x4<T> translationMatrix = Matrix4x4<T>::translation(position);
    Matrix4x4<T> rotationMatrix = rotation.toMatrix();
    Matrix4x4<T> scaleMatrix = Matrix4x4<T>::scale(scale.x, scale.y, scale.z);
    
    return translationMatrix * rotationMatrix * scaleMatrix;
}

template<typename T>
Matrix4x4<T> Transform<T>::getInverseMatrix() const {
    Matrix4x4<T> translationMatrix = Matrix4x4<T>::translation(-position);
    Matrix4x4<T> rotationMatrix = rotation.inverse().toMatrix();
    Matrix4x4<T> scaleMatrix = Matrix4x4<T>::scale(1 / scale.x, 1 / scale.y, 1 / scale.z);
    
    return scaleMatrix * rotationMatrix * translationMatrix;
}

// Transformation methods

template<typename T>
Vector3<T> Transform<T>::transformPoint(const Vector3<T>& point) const {
    Matrix4x4<T> matrix = getMatrix();
    return matrix.transformPoint(point);
}

template<typename T>
Vector3<T> Transform<T>::transformVector(const Vector3<T>& vector) const {
    Matrix4x4<T> matrix = getMatrix();
    return matrix.transformVector(vector);
}

// Combining transforms

template<typename T>
Transform<T> Transform<T>::combine(const Transform<T>& other) const {
    Vector3<T> newPosition = position + rotation * (other.position * scale);
    Quaternion<T> newRotation = rotation * other.rotation;
    Vector3<T> newScale = scale * other.scale;
    
    return Transform<T>(newPosition, newRotation, newScale);
}

// Interpolation

template<typename T>
Transform<T> Transform<T>::lerp(const Transform<T>& a, const Transform<T>& b, T t) {
    Vector3<T> position = Vector3<T>::lerp(a.position, b.position, t);
    Quaternion<T> rotation = Quaternion<T>::lerp(a.rotation, b.rotation, t);
    Vector3<T> scale = Vector3<T>::lerp(a.scale, b.scale, t);
    
    return Transform<T>(position, rotation, scale);
}

// Getters and setters

template<typename T>
void Transform<T>::setPosition(const Vector3<T>& pos) {
    position = pos;
}

template<typename T>
void Transform<T>::setRotation(const Quaternion<T>& rot) {
    rotation = rot;
}

template<typename T>
void Transform<T>::setScale(const Vector3<T>& scl) {
    scale = scl;
}

template<typename T>
Vector3<T> Transform<T>::getPosition() const {
    return position;
}

template<typename T>
Quaternion<T> Transform<T>::getRotation() const {
    return rotation;
}

template<typename T>
Vector3<T> Transform<T>::getScale() const {
    return scale;
}

// Local transformations

template<typename T>
void Transform<T>::translate(const Vector3<T>& translation) {
    position = position + rotation * (translation * scale);
}

template<typename T>
void Transform<T>::rotate(const Quaternion<T>& rot) {
    rotation = rotation * rot;
}

template<typename T>
void Transform<T>::scaleBy(const Vector3<T>& scaling) {
    scale = scale * scaling;
}

template<typename T>
Matrix4x4<T> Transform<T>::getModelMatrix() const {
    // M = T * R * S (Scale, then Rotate, then Translate)
    return buildModelMatrix(position, rotation, scale);
}

template<typename T>
Matrix4x4<T> Transform<T>::buildModelMatrix(const Vector3<T>& position, 
                                           const Quaternion<T>& rotation, 
                                           const Vector3<T>& scale) {
    Matrix4x4<T> translationMat = Matrix4x4<T>::translation(position);
    Matrix4x4<T> rotationMat = rotation.toMatrix();
    Matrix4x4<T> scaleMat = Matrix4x4<T>::scaling(scale);
    
    return translationMat * rotationMat * scaleMat;
}

template<typename T>
Vector3<T> Transform<T>::transformPoint(const Vector3<T>& point) const {
    // Transform from model space to world space
    return getModelMatrix().transformPoint(point);
}

template<typename T>
Vector3<T> Transform<T>::inverseTransformPoint(const Vector3<T>& point) const {
    // Transform from world space to model space
    return getInverseModelMatrix().transformPoint(point);
}

template<typename T>
Vector3<T> Transform<T>::transformVector(const Vector3<T>& vector) const {
    // For direction vectors (no translation)
    return rotation.rotate(vector) * scale; // Apply rotation and scale only
}
