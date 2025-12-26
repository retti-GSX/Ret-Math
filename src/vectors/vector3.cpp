#include "../../include/vectors/vector3.hpp"

// Constructor

template<typename T>
Vector3<T>::Vector3(T x, T y, T z) : x(x), y(y), z(z) {}

// Operator overloads

template<typename T>
Vector3<T> Vector3<T>::operator+(const Vector3<T>& other) const {
    return Vector3<T>(x + other.x, y + other.y, z + other.z);
}

template<typename T>
Vector3<T> Vector3<T>::operator-(const Vector3<T>& other) const {
    return Vector3<T>(x - other.x, y - other.y, z - other.z);
}

template<typename T>
Vector3<T> Vector3<T>::operator-() const {
    return Vector3<T>(-x, -y, -z);
}

template<typename T>
Vector3<T> Vector3<T>::operator*(T scalar) const {
    return Vector3<T>(x * scalar, y * scalar, z * scalar);
}

template<typename T>
Vector3<T> Vector3<T>::operator/(T scalar) const {
    return Vector3<T>(x / scalar, y / scalar, z / scalar);
}

// Vector operations

template<typename T>
Vector3<T> Vector3<T>::cross(const Vector3<T>& other) const {
    return Vector3<T>(
        y * other.z - z * other.y,
        z * other.x - x * other.z,
        x * other.y - y * other.x
    );
}

template<typename T>
T Vector3<T>::dot(const Vector3<T>& other) const {
    return x * other.x + y * other.y + z * other.z;
}

template<typename T>
T Vector3<T>::length() const {
    return std::sqrt(x * x + y * y + z * z);
}

template<typename T>
T Vector3<T>::lengthSquared() const {
    return x * x + y * y + z * z;
}

template<typename T>
Vector3<T> Vector3<T>::normalized() const {
    T len = length();
    if (len > 0) {
        return Vector3<T>(x / len, y / len, z / len);
    }
    return Vector3<T>(0, 0, 0);
}

template<typename T>
void Vector3<T>::normalize() {
    T len = length();
    if (len > 0) {
        x /= len;
        y /= len;
        z /= len;
    }
}

template<typename T>
Vector3<T> Vector3<T>::rotatedX(T angle) const {
    T cosAngle = std::cos(angle);
    T sinAngle = std::sin(angle);
    return Vector3<T>(
        x,
        y * cosAngle - z * sinAngle,
        y * sinAngle + z * cosAngle
    );
}

template<typename T>
Vector3<T> Vector3<T>::rotatedY(T angle) const {
    T cosAngle = std::cos(angle);
    T sinAngle = std::sin(angle);
    return Vector3<T>(
        x * cosAngle + z * sinAngle,
        y,
        -x * sinAngle + z * cosAngle
    );
}

template<typename T>
Vector3<T> Vector3<T>::rotatedZ(T angle) const {
    T cosAngle = std::cos(angle);
    T sinAngle = std::sin(angle);
    return Vector3<T>(
        x * cosAngle - y * sinAngle,
        x * sinAngle + y * cosAngle,
        z
    );
}

template<typename T>
bool Vector3<T>::equals(const Vector3<T>& other, T epsilon) const {
    return std::abs(x - other.x) <= epsilon &&
           std::abs(y - other.y) <= epsilon &&
           std::abs(z - other.z) <= epsilon;
}

// Static methods

template<typename T>
Vector3<T> Vector3<T>::lerp(const Vector3<T>& a, const Vector3<T>& b, T t) {
    return Vector3<T>(
        a.x + (b.x - a.x) * t,
        a.y + (b.y - a.y) * t,
        a.z + (b.z - a.z) * t
    );
}

// Explicit template instantiations
template class Vector3<float>;
template class Vector3<int>;
template class Vector3<double>;