#pragma once
#include "../vectors/vector3.hpp"
#include "matrix2x2.hpp"
#include <cmath>

template<typename T>
class Matrix4x4;

template<typename T>
class Matrix3x3 {
private:
    T m[3][3];
    
public:
    Matrix3x3();
    Matrix3x3(T identity);
    Matrix3x3(T m00, T m01, T m02,
             T m10, T m11, T m12,
             T m20, T m21, T m22);
    
    static Matrix3x3 identity();
    static Matrix3x3 translation(T x, T y);
    static Matrix3x3 translation(const Vector2<T>& vec);
    static Matrix3x3 rotation(T angle);
    static Matrix3x3 rotationX(T angle);
    static Matrix3x3 rotationY(T angle);
    static Matrix3x3 rotationZ(T angle);
    static Matrix3x3 scale(T sx, T sy, T sz);
    static Matrix3x3 scale(T s);
    static Matrix3x3 scale(const Vector3<T>& scale);
    static Matrix3x3 fromMatrix2x2(const Matrix2x2<T>& mat2);
    
    Matrix3x3 operator+(const Matrix3x3& other) const;
    Matrix3x3 operator-(const Matrix3x3& other) const;
    Matrix3x3 operator*(const Matrix3x3& other) const;
    Matrix3x3 operator*(T scalar) const;
    Vector3<T> operator*(const Vector3<T>& vec) const;
    bool operator==(const Matrix3x3& other) const;
    
    Vector2<T> transformPoint(const Vector2<T>& point) const;
    Vector2<T> transformVector(const Vector2<T>& vector) const;
    
    Matrix3x3 inverse() const;
    Matrix3x3 transposed() const;
    T determinant() const;
    T trace() const;
    
    Matrix2x2<T> submatrix(int excludedRow, int excludedCol) const;
    T minor(int row, int col) const;
    T cofactor(int row, int col) const;
    
    T& operator()(int row, int col);
    const T& operator()(int row, int col) const;
    
    Vector3<T> getRow(int row) const;
    Vector3<T> getColumn(int col) const;
    
    bool isOrthogonal() const;
    void orthonormalize();
    
    static Matrix3x3 fromAxisAngle(const Vector3<T>& axis, T angle);
    
    Matrix4x4<T> toMatrix4x4() const;
};

using Matrix3x3f = Matrix3x3<float>;
using Matrix3x3i = Matrix3x3<int>;
