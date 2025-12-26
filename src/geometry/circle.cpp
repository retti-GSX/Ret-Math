#include "../../include/geometry/circle.hpp"

// Constructors

template<typename T>
Circle<T>::Circle(const Vector2<T>& center, T radius) : center(center), radius(radius) {}

template<typename T>
Circle<T>::Circle(T x, T y, T radius) : center(Vector2<T>(x, y)), radius(radius) {}

// Containment and intersection

template<typename T>
bool Circle<T>::contains(const Vector2<T>& point) const {
    return (point - center).lengthSquared() <= radius * radius;
}

template<typename T>
bool Circle<T>::contains(const Circle<T>& other) const {
    T distance = (other.center - center).length();
    return distance + other.radius <= radius;
}

template<typename T>
bool Circle<T>::intersects(const Circle<T>& other) const {
    T distance = (other.center - center).length();
    return distance <= radius + other.radius && distance >= std::abs(radius - other.radius);
}

template<typename T>
bool Circle<T>::intersects(const Rect<T>& rect) const {
    Vector2<T> closestPoint = Vector2<T>(
        std::clamp(center.x, rect.left(), rect.right()),
        std::clamp(center.y, rect.top(), rect.bottom())
    );
    return (closestPoint - center).lengthSquared() <= radius * radius;
}

// Area and circumference

template<typename T>
T Circle<T>::area() const {
    return static_cast<T>(3.14159265358979323846) * radius * radius;
}

template<typename T>
T Circle<T>::circumference() const {
    return static_cast<T>(2 * 3.14159265358979323846) * radius;
}

// Bounding rect

template<typename T>
Rect<T> Circle<T>::boundingRect() const {
    return Rect<T>(center.x - radius, center.y - radius, radius * 2, radius * 2);
}

// Transformations

template<typename T>
Circle<T> Circle<T>::transformed(const Matrix3x3<T>& transform) const {
    Vector2<T> newCenter = transform.transformPoint(center);
    Vector3<T> row0 = transform.getRow(0);
    Vector2<T> scale(row0.x, row0.y);
    T newRadius = radius * scale.length();
    return Circle<T>(newCenter, newRadius);
}

template<typename T>
T Circle<T>::distanceTo(const Vector2<T>& point) const {
    return (point - center).length() - radius;
}

template<typename T>
Vector2<T> Circle<T>::pointAtAngle(T angle) const {
    return Vector2<T>(center.x + radius * std::cos(angle), center.y + radius * std::sin(angle));
}

// Ray intersection

template<typename T>
bool Circle<T>::intersectRay(const Vector2<T>& origin, const Vector2<T>& direction,
                            T& t1, T& t2, Vector2<T>& point1, Vector2<T>& point2) const {
    Vector2<T> toCenter = center - origin;
    T a = direction.dot(direction);
    T b = 2 * toCenter.dot(direction);
    T c = toCenter.dot(toCenter) - radius * radius;
    T discriminant = b * b - 4 * a * c;
    
    if (discriminant < 0) {
        return false;
    }
    
    discriminant = std::sqrt(discriminant);
    t1 = (-b - discriminant) / (2 * a);
    t2 = (-b + discriminant) / (2 * a);
    
    point1 = origin + direction * t1;
    point2 = origin + direction * t2;

    return true;
}

// Explicit template instantiations
template class Circle<float>;
template class Circle<int>;