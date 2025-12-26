#pragma once
#include "../vectors/vector2.hpp"
#include "rect.hpp"
#include "../matrices/matrix3x3.hpp"
#include <cmath>

template<typename T>
class Circle {
public:
    Vector2<T> center;
    T radius;
    
    Circle(const Vector2<T>& center = Vector2<T>(), T radius = 0);
    Circle(T x, T y, T radius);
    
    bool contains(const Vector2<T>& point) const;
    bool contains(const Circle& other) const;
    bool intersects(const Circle& other) const;
    bool intersects(const Rect<T>& rect) const;
    
    T area() const;
    T circumference() const;
    
    Rect<T> boundingRect() const;
    Circle transformed(const Matrix3x3<T>& transform) const;
    T distanceTo(const Vector2<T>& point) const;
    Vector2<T> pointAtAngle(T angle) const;
    
    bool intersectRay(const Vector2<T>& origin, const Vector2<T>& direction,
                     T& t1, T& t2, Vector2<T>& point1, Vector2<T>& point2) const;
};

using Circlef = Circle<float>;
using Circlei = Circle<int>;