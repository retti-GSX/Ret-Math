#include "../../include/vectors/vector4.hpp"

// Constructors

template<typename T>
Vector4<T>::Vector4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}

template<typename T>
Vector4<T>::Vector4(const Vector3<T>& vec3, T w) : x(vec3.x), y(vec3.y), z(vec3.z), w(w) {}

// Operator overloads

template<typename T>
Vector4<T> Vector4<T>::operator+(const Vector4<T>& other) const {
    return Vector4<T>(x + other.x, y + other.y, z + other.z, w + other.w);
}

template<typename T>
Vector4<T> Vector4<T>::operator-(const Vector4<T>& other) const {
    return Vector4<T>(x - other.x, y - other.y, z - other.z, w - other.w);
}

template<typename T>
Vector4<T> Vector4<T>::operator*(T scalar) const {
    return Vector4<T>(x * scalar, y * scalar, z * scalar, w * scalar);
}

template<typename T>
Vector4<T> Vector4<T>::operator/(T scalar) const {
    return Vector4<T>(x / scalar, y / scalar, z / scalar, w / scalar);
}

// Vector operations

template<typename T>
Vector3<T> Vector4<T>::xyz() const {
    return Vector3<T>(x, y, z);
}

template<typename T>
Vector3<T> Vector4<T>::homogeneous() const {
    if (w != 0) {
        return Vector3<T>(x / w, y / w, z / w);
    }
    return Vector3<T>(x, y, z);
}

// Static methods

template<typename T>
Vector4<T> Vector4<T>::fromRGBA(T r, T g, T b, T a) {
    return Vector4<T>(r, g, b, a);
}

// Explicit template instantiations
template class Vector4<float>;
template class Vector4<int>;
template class Vector4<double>;