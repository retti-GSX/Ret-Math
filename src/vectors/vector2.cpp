#include "../../include/vectors/vector2.hpp"

// Constructor

template<typename T>
Vector2<T>::Vector2(T x, T y) : x(x), y(y) {}

// Operator overloads

template<typename T>
Vector2<T> Vector2<T>::operator+(const Vector2<T>& other) const {
    return Vector2<T>(x + other.x, y + other.y);
}

template<typename T>
Vector2<T> Vector2<T>::operator-(const Vector2<T>& other) const {
    return Vector2<T>(x - other.x, y - other.y);
}

template<typename T>
Vector2<T> Vector2<T>::operator*(T scalar) const {
    return Vector2<T>(x * scalar, y * scalar);
}

template<typename T>
Vector2<T> Vector2<T>::operator/(T scalar) const {
    return Vector2<T>(x / scalar, y / scalar);
}

// Vector operations

template<typename T>
T Vector2<T>::length() const {
    return std::sqrt(x * x + y * y);
}

template<typename T>
T Vector2<T>::lengthSquared() const {
    return x * x + y * y;
}

template<typename T>
Vector2<T> Vector2<T>::normalized() const {
    T len = length();
    if (len > 0) {
        return Vector2<T>(x / len, y / len);
    }
    return Vector2<T>(0, 0);
}

template<typename T>
void Vector2<T>::normalize() {
    T len = length();
    if (len > 0) {
        x /= len;
        y /= len;
    }
}

template<typename T>
T Vector2<T>::dot(const Vector2<T>& other) const {
    return x * other.x + y * other.y;
}

template<typename T>
T Vector2<T>::cross(const Vector2<T>& other) const {
    return x * other.y - y * other.x;
}

// Static methods

template<typename T>
Vector2<T> Vector2<T>::lerp(const Vector2<T>& a, const Vector2<T>& b, T t) {
    return Vector2<T>(a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t);
}

// Explicit template instantiations
template class Vector2<float>;
template class Vector2<int>;
template class Vector2<double>;
