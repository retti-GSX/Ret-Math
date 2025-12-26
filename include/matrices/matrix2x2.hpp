#pragma once
#include "../vectors/vector2.hpp"
#include <cmath>

template<typename T>
class Matrix2x2 {
private:
    T m[2][2];
    
public:
    Matrix2x2();
    Matrix2x2(T identity);
    Matrix2x2(T m00, T m01, T m10, T m11);
    
    static Matrix2x2 identity();
    static Matrix2x2 rotation(T angle);
    static Matrix2x2 scale(T sx, T sy);
    static Matrix2x2 scale(T s);
    static Matrix2x2 shearX(T factor);
    static Matrix2x2 shearY(T factor);
    
    Matrix2x2 operator+(const Matrix2x2& other) const;
    Matrix2x2 operator-(const Matrix2x2& other) const;
    Matrix2x2 operator*(const Matrix2x2& other) const;
    Matrix2x2 operator*(T scalar) const;
    Vector2<T> operator*(const Vector2<T>& vec) const;
    bool operator==(const Matrix2x2& other) const;
    
    Matrix2x2 inverse() const;
    Matrix2x2 transposed() const;
    T determinant() const;
    T trace() const;
    
    static Matrix2x2 diagonal(T d1, T d2);
    
    T& operator()(int row, int col);
    const T& operator()(int row, int col) const;
    
    Vector2<T> getRow(int row) const;
    Vector2<T> getColumn(int col) const;
    
    bool isOrthogonal() const;
    
    static Vector2<T> rotateVector(const Vector2<T>& vec, T angle);
};

using Matrix2x2f = Matrix2x2<float>;
using Matrix2x2i = Matrix2x2<int>;
