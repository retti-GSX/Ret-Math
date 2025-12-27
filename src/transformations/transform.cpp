#include "../../include/transformations/transform.hpp"

// Constructors

template<typename T>
Transform<T>::Transform() : position(Vector3<T>()), rotation(Quaternion<T>()), scale(Vector3<T>(1, 1, 1)) {}

template<typename T>
Transform<T>::Transform(const Vector3<T>& pos, const Quaternion<T>& rot, const Vector3<T>& scl)
    : position(pos), rotation(rot), scale(scl) {}

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

// Transform directions

template<typename T>
Vector3<T> Transform<T>::forward() const {
    return rotation.rotate(Vector3<T>(0, 0, 1));
}

template<typename T>
Vector3<T> Transform<T>::up() const {
    return rotation.rotate(Vector3<T>(0, 1, 0));
}

template<typename T>
Vector3<T> Transform<T>::right() const {
    return rotation.rotate(Vector3<T>(1, 0, 0));
}
