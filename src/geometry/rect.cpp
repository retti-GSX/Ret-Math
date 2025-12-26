#include "../../include/geometry/rect.hpp"

// Constructors

template<typename T>
Rect<T>::Rect(T x, T y, T width, T height) : x(x), y(y), width(width), height(height) {}

template<typename T>
Rect<T>::Rect(const Vector2<T>& position, const Vector2<T>& size) : x(position.x), y(position.y), width(size.x), height(size.y) {}

// Properties

template<typename T>
T Rect<T>::left() const { return x; }

template<typename T>
T Rect<T>::right() const { return x + width; }

template<typename T>
T Rect<T>::top() const { return y; }

template<typename T>
T Rect<T>::bottom() const { return y + height; }

template<typename T>
Vector2<T> Rect<T>::position() const { return Vector2<T>(x, y); }

template<typename T>
Vector2<T> Rect<T>::size() const { return Vector2<T>(width, height); }

template<typename T>
Vector2<T> Rect<T>::center() const { return Vector2<T>(x + width / 2, y + height / 2); }

template<typename T>
Vector2<T> Rect<T>::topLeft() const { return Vector2<T>(left(), top()); }

template<typename T>
Vector2<T> Rect<T>::topRight() const { return Vector2<T>(right(), top()); }

template<typename T>
Vector2<T> Rect<T>::bottomLeft() const { return Vector2<T>(left(), bottom()); }

template<typename T>
Vector2<T> Rect<T>::bottomRight() const { return Vector2<T>(right(), bottom()); }

// Containment and intersection

template<typename T>
bool Rect<T>::contains(T px, T py) const {
    return px >= left() && px <= right() && py >= top() && py <= bottom();
}

template<typename T>
bool Rect<T>::contains(const Vector2<T>& point) const {
    return contains(point.x, point.y);
}

template<typename T>
bool Rect<T>::contains(const Rect<T>& other) const {
    return other.left() >= left() && other.right() <= right() &&
           other.top() >= top() && other.bottom() <= bottom();
}

template<typename T>
bool Rect<T>::intersects(const Rect<T>& other) const {
    return !(other.left() > right() || other.right() < left() ||
             other.top() > bottom() || other.bottom() < top());
}

// Operator overloads

template<typename T>
Rect<T> Rect<T>::operator+(const Vector2<T>& offset) const {
    return Rect<T>(x + offset.x, y + offset.y, width, height);
}

template<typename T>
Rect<T> Rect<T>::operator-(const Vector2<T>& offset) const {
    return Rect<T>(x - offset.x, y - offset.y, width, height);
}

template<typename T>
Rect<T>& Rect<T>::operator+=(const Vector2<T>& offset) {
    x += offset.x;
    y += offset.y;
    return *this;
}

template<typename T>
Rect<T>& Rect<T>::operator-=(const Vector2<T>& offset) {
    x -= offset.x;
    y -= offset.y;
    return *this;
}

// Union and intersection

template<typename T>
Rect<T> Rect<T>::unionWith(const Rect<T>& other) const {
    T newLeft = std::min(left(), other.left());
    T newRight = std::max(right(), other.right());
    T newTop = std::min(top(), other.top());
    T newBottom = std::max(bottom(), other.bottom());
    return Rect<T>(newLeft, newTop, newRight - newLeft, newBottom - newTop);
}

template<typename T>
Rect<T> Rect<T>::intersection(const Rect<T>& other) const {
    T newLeft = std::max(left(), other.left());
    T newRight = std::min(right(), other.right());
    T newTop = std::max(top(), other.top());
    T newBottom = std::min(bottom(), other.bottom());
    return Rect<T>(newLeft, newTop, newRight - newLeft, newBottom - newTop);
}

// Expansion

template<typename T>
Rect<T> Rect<T>::expanded(T amount) const {
    return expanded(amount, amount);
}

template<typename T>
Rect<T> Rect<T>::expanded(T horizontal, T vertical) const {
    return Rect<T>(x - horizontal, y - vertical, width + horizontal * 2, height + vertical * 2);
}

template<typename T>
Rect<T> Rect<T>::expanded(const Vector2<T>& amount) const {
    return expanded(amount.x, amount.y);
}

// Scaling

template<typename T>
Rect<T> Rect<T>::scaled(T scale) const {
    return scaled(scale, scale);
}

template<typename T>
Rect<T> Rect<T>::scaled(T scaleX, T scaleY) const {
    return Rect<T>(x, y, width * scaleX, height * scaleY);
}

// Empty check

template<typename T>
bool Rect<T>::isEmpty() const {
    return width <= 0 || height <= 0;
}

template<typename T>
Rect<T> Rect<T>::normalized() const {
    Rect<T> result = *this;
    if (result.width < 0) {
        result.x += result.width;
        result.width = -result.width;
    }
    if (result.height < 0) {
        result.y += result.height;
        result.height = -result.height;
    }
    return result;
}

template<typename T>
void Rect<T>::normalize() {
    *this = normalized();
}

// Transformation

template<typename T>
Rect<T> Rect<T>::transformed(const Matrix3x3<T>& transform) const {
    Vector2<T> newTopLeft = transform.transformPoint(topLeft());
    Vector2<T> newTopRight = transform.transformPoint(topRight());
    Vector2<T> newBottomLeft = transform.transformPoint(bottomLeft());
    Vector2<T> newBottomRight = transform.transformPoint(bottomRight());
    
    T minX = std::min(std::min(newTopLeft.x, newTopRight.x), std::min(newBottomLeft.x, newBottomRight.x));
    T maxX = std::max(std::max(newTopLeft.x, newTopRight.x), std::max(newBottomLeft.x, newBottomRight.x));
    T minY = std::min(std::min(newTopLeft.y, newTopRight.y), std::min(newBottomLeft.y, newBottomRight.y));
    T maxY = std::max(std::max(newTopLeft.y, newTopRight.y), std::max(newBottomLeft.y, newBottomRight.y));
    
    return Rect<T>(minX, minY, maxX - minX, maxY - minY);
}

// Static methods

template<typename T>
Rect<T> Rect<T>::fromPoints(const Vector2<T>& p1, const Vector2<T>& p2) {
    T left = std::min(p1.x, p2.x);
    T top = std::min(p1.y, p2.y);
    T right = std::max(p1.x, p2.x);
    T bottom = std::max(p1.y, p2.y);
    return Rect<T>(left, top, right - left, bottom - top);
}

template<typename T>
Rect<T> Rect<T>::fromCenter(const Vector2<T>& center, T width, T height) {
    return Rect<T>(center.x - width / 2, center.y - height / 2, width, height);
}

template<typename T>
Rect<T> Rect<T>::fromCenter(const Vector2<T>& center, const Vector2<T>& size) {
    return fromCenter(center, size.x, size.y);
}

// Explicit template instantiations
template class Rect<float>;
template class Rect<int>;