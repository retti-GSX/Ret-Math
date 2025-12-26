#pragma once
#include "../vectors/vector2.hpp"
#include "../matrices/matrix3x3.hpp"
#include <algorithm>

template<typename T>
class Rect {
public:
    T x, y, width, height;
    
    Rect(T x = 0, T y = 0, T width = 0, T height = 0);
    Rect(const Vector2<T>& position, const Vector2<T>& size);
    
    T left() const;
    T right() const;
    T top() const;
    T bottom() const;
    
    Vector2<T> position() const;
    Vector2<T> size() const;
    Vector2<T> center() const;
    
    Vector2<T> topLeft() const;
    Vector2<T> topRight() const;
    Vector2<T> bottomLeft() const;
    Vector2<T> bottomRight() const;
    
    bool contains(T px, T py) const;
    bool contains(const Vector2<T>& point) const;
    bool contains(const Rect& other) const;
    bool intersects(const Rect& other) const;
    
    Rect operator+(const Vector2<T>& offset) const;
    Rect operator-(const Vector2<T>& offset) const;
    Rect& operator+=(const Vector2<T>& offset);
    Rect& operator-=(const Vector2<T>& offset);
    
    Rect unionWith(const Rect& other) const;
    Rect intersection(const Rect& other) const;
    
    Rect expanded(T amount) const;
    Rect expanded(T horizontal, T vertical) const;
    Rect expanded(const Vector2<T>& amount) const;
    
    Rect scaled(T scale) const;
    Rect scaled(T scaleX, T scaleY) const;
    
    bool isEmpty() const;
    Rect normalized() const;
    void normalize();
    
    Rect transformed(const Matrix3x3<T>& transform) const;
    
    static Rect fromPoints(const Vector2<T>& p1, const Vector2<T>& p2);
    static Rect fromCenter(const Vector2<T>& center, T width, T height);
    static Rect fromCenter(const Vector2<T>& center, const Vector2<T>& size);
};

using Rectf = Rect<float>;
using Recti = Rect<int>;