#pragma once
#include "../vectors/vector3.hpp"
#include "../vectors/vector4.hpp"
#include <cmath>

template<typename T>
class Matrix4x4 {
public:
    T m[4][4];
    
    Matrix4x4();
    Matrix4x4(T identity);
    
    // Added constructor for explicit initialization of all elements
    Matrix4x4(T m00, T m01, T m02, T m03,
              T m10, T m11, T m12, T m13,
              T m20, T m21, T m22, T m23,
              T m30, T m31, T m32, T m33);
    
    static Matrix4x4 identity();
    static Matrix4x4 translation(T x, T y, T z);
    static Matrix4x4 translation(const Vector3<T>& vec);
    static Matrix4x4 scale(T x, T y, T z);
    static Matrix4x4 rotationX(T angle);
    static Matrix4x4 rotationY(T angle);
    static Matrix4x4 rotationZ(T angle);
    static Matrix4x4 perspective(T fov, T aspect, T near, T far);
    static Matrix4x4 orthographic(T left, T right, T bottom, T top, T near, T far);
    static Matrix4x4 lookAt(const Vector3<T>& eye, const Vector3<T>& target, const Vector3<T>& up);
    
    Matrix4x4 operator*(const Matrix4x4& other) const;
    Vector4<T> operator*(const Vector4<T>& vec) const;
    bool operator==(const Matrix4x4& other) const;
    
    Vector3<T> transformPoint(const Vector3<T>& point) const;
    Vector3<T> transformVector(const Vector3<T>& vector) const;
    
    Matrix4x4 inverse() const;
    Matrix4x4 transposed() const;
    
    T* operator[](int row);
    const T* operator[](int row) const;
    
    // Added for access to internal data
    T& operator()(int row, int col);
    const T& operator()(int row, int col) const;
};

using Matrix4x4f = Matrix4x4<float>;
using Matrix4x4d = Matrix4x4<double>;  // Added for double
