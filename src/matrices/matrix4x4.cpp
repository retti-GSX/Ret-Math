#include "../../include/matrices/matrix4x4.hpp"

// Constructors

template<typename T>
Matrix4x4<T>::Matrix4x4() {
    m[0][0] = 1; m[0][1] = 0; m[0][2] = 0; m[0][3] = 0;
    m[1][0] = 0; m[1][1] = 1; m[1][2] = 0; m[1][3] = 0;
    m[2][0] = 0; m[2][1] = 0; m[2][2] = 1; m[2][3] = 0;
    m[3][0] = 0; m[3][1] = 0; m[3][2] = 0; m[3][3] = 1;
}

template<typename T>
Matrix4x4<T>::Matrix4x4(T identity) {
    m[0][0] = identity; m[0][1] = 0; m[0][2] = 0; m[0][3] = 0;
    m[1][0] = 0; m[1][1] = identity; m[1][2] = 0; m[1][3] = 0;
    m[2][0] = 0; m[2][1] = 0; m[2][2] = identity; m[2][3] = 0;
    m[3][0] = 0; m[3][1] = 0; m[3][2] = 0; m[3][3] = identity;
}

// Added constructor for explicit initialization of all elements
template<typename T>
Matrix4x4<T>::Matrix4x4(T m00, T m01, T m02, T m03,
                       T m10, T m11, T m12, T m13,
                       T m20, T m21, T m22, T m23,
                       T m30, T m31, T m32, T m33) {
    m[0][0] = m00; m[0][1] = m01; m[0][2] = m02; m[0][3] = m03;
    m[1][0] = m10; m[1][1] = m11; m[1][2] = m12; m[1][3] = m13;
    m[2][0] = m20; m[2][1] = m21; m[2][2] = m22; m[2][3] = m23;
    m[3][0] = m30; m[3][1] = m31; m[3][2] = m32; m[3][3] = m33;
}

// Static methods

template<typename T>
Matrix4x4<T> Matrix4x4<T>::identity() {
    return Matrix4x4<T>(1);
}

template<typename T>
Matrix4x4<T> Matrix4x4<T>::translation(T x, T y, T z) {
    Matrix4x4<T> result;
    result.m[0][3] = x;
    result.m[1][3] = y;
    result.m[2][3] = z;
    return result;
}

template<typename T>
Matrix4x4<T> Matrix4x4<T>::translation(const Vector3<T>& vec) {
    return translation(vec.x, vec.y, vec.z);
}

template<typename T>
Matrix4x4<T> Matrix4x4<T>::scale(T x, T y, T z) {
    Matrix4x4<T> result;
    result.m[0][0] = x;
    result.m[1][1] = y;
    result.m[2][2] = z;
    return result;
}

template<typename T>
Matrix4x4<T> Matrix4x4<T>::rotationX(T angle) {
    T cosAngle = static_cast<T>(std::cos(angle));
    T sinAngle = static_cast<T>(std::sin(angle));
    Matrix4x4<T> result;
    result.m[1][1] = cosAngle;
    result.m[1][2] = -sinAngle;
    result.m[2][1] = sinAngle;
    result.m[2][2] = cosAngle;
    return result;
}

template<typename T>
Matrix4x4<T> Matrix4x4<T>::rotationY(T angle) {
    T cosAngle = static_cast<T>(std::cos(angle));
    T sinAngle = static_cast<T>(std::sin(angle));
    Matrix4x4<T> result;
    result.m[0][0] = cosAngle;
    result.m[0][2] = sinAngle;
    result.m[2][0] = -sinAngle;
    result.m[2][2] = cosAngle;
    return result;
}

template<typename T>
Matrix4x4<T> Matrix4x4<T>::rotationZ(T angle) {
    T cosAngle = static_cast<T>(std::cos(angle));
    T sinAngle = static_cast<T>(std::sin(angle));
    Matrix4x4<T> result;
    result.m[0][0] = cosAngle;
    result.m[0][1] = -sinAngle;
    result.m[1][0] = sinAngle;
    result.m[1][1] = cosAngle;
    return result;
}

template<typename T>
Matrix4x4<T> Matrix4x4<T>::perspective(T fov, T aspect, T near, T far) {
    T tanHalfFov = static_cast<T>(std::tan(fov / 2));
    Matrix4x4<T> result;
    result.m[0][0] = 1 / (aspect * tanHalfFov);
    result.m[1][1] = 1 / tanHalfFov;
    result.m[2][2] = -(far + near) / (far - near);
    result.m[2][3] = -1;
    result.m[3][2] = -(2 * far * near) / (far - near);
    result.m[3][3] = 0;
    return result;
}

template<typename T>
Matrix4x4<T> Matrix4x4<T>::orthographic(T left, T right, T bottom, T top, T near, T far) {
    Matrix4x4<T> result;
    result.m[0][0] = 2 / (right - left);
    result.m[1][1] = 2 / (top - bottom);
    result.m[2][2] = -2 / (far - near);
    result.m[0][3] = -(right + left) / (right - left);
    result.m[1][3] = -(top + bottom) / (top - bottom);
    result.m[2][3] = -(far + near) / (far - near);
    return result;
}

template<typename T>
Matrix4x4<T> Matrix4x4<T>::lookAt(const Vector3<T>& eye, const Vector3<T>& target, const Vector3<T>& up) {
    Vector3<T> zaxis = (eye - target).normalized();
    Vector3<T> xaxis = up.cross(zaxis).normalized();
    Vector3<T> yaxis = zaxis.cross(xaxis);
    
    Matrix4x4<T> result;
    result.m[0][0] = xaxis.x;
    result.m[0][1] = xaxis.y;
    result.m[0][2] = xaxis.z;
    result.m[1][0] = yaxis.x;
    result.m[1][1] = yaxis.y;
    result.m[1][2] = yaxis.z;
    result.m[2][0] = zaxis.x;
    result.m[2][1] = zaxis.y;
    result.m[2][2] = zaxis.z;
    result.m[0][3] = -xaxis.dot(eye);
    result.m[1][3] = -yaxis.dot(eye);
    result.m[2][3] = -zaxis.dot(eye);
    return result;
}

// Operator overloads

template<typename T>
Matrix4x4<T> Matrix4x4<T>::operator*(const Matrix4x4<T>& other) const {
    Matrix4x4<T> result;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            result.m[i][j] = m[i][0] * other.m[0][j] +
                            m[i][1] * other.m[1][j] +
                            m[i][2] * other.m[2][j] +
                            m[i][3] * other.m[3][j];
        }
    }
    return result;
}

template<typename T>
Vector4<T> Matrix4x4<T>::operator*(const Vector4<T>& vec) const {
    return Vector4<T>(
        m[0][0] * vec.x + m[0][1] * vec.y + m[0][2] * vec.z + m[0][3] * vec.w,
        m[1][0] * vec.x + m[1][1] * vec.y + m[1][2] * vec.z + m[1][3] * vec.w,
        m[2][0] * vec.x + m[2][1] * vec.y + m[2][2] * vec.z + m[2][3] * vec.w,
        m[3][0] * vec.x + m[3][1] * vec.y + m[3][2] * vec.z + m[3][3] * vec.w
    );
}

template<typename T>
Vector3<T> Matrix4x4<T>::transformPoint(const Vector3<T>& point) const {
    Vector4<T> vec4(point.x, point.y, point.z, 1);
    Vector4<T> result = (*this) * vec4;
    return Vector3<T>(result.x, result.y, result.z);
}

template<typename T>
Vector3<T> Matrix4x4<T>::transformVector(const Vector3<T>& vector) const {
    Vector4<T> vec4(vector.x, vector.y, vector.z, 0);
    Vector4<T> result = (*this) * vec4;
    return Vector3<T>(result.x, result.y, result.z);
}

template<typename T>
Matrix4x4<T> Matrix4x4<T>::inverse() const {
    Matrix4x4<T> inv;
    T det;
    
    // Calculating the matrix of algebraic complements
    inv.m[0][0] = m[1][1] * m[2][2] * m[3][3] - m[1][1] * m[2][3] * m[3][2] - 
                  m[2][1] * m[1][2] * m[3][3] + m[2][1] * m[1][3] * m[3][2] + 
                  m[3][1] * m[1][2] * m[2][3] - m[3][1] * m[1][3] * m[2][2];

    inv.m[1][0] = -m[1][0] * m[2][2] * m[3][3] + m[1][0] * m[2][3] * m[3][2] + 
                   m[2][0] * m[1][2] * m[3][3] - m[2][0] * m[1][3] * m[3][2] - 
                   m[3][0] * m[1][2] * m[2][3] + m[3][0] * m[1][3] * m[2][2];

    inv.m[2][0] = m[1][0] * m[2][1] * m[3][3] - m[1][0] * m[2][3] * m[3][1] - 
                  m[2][0] * m[1][1] * m[3][3] + m[2][0] * m[1][3] * m[3][1] + 
                  m[3][0] * m[1][1] * m[2][3] - m[3][0] * m[1][3] * m[2][1];

    inv.m[3][0] = -m[1][0] * m[2][1] * m[3][2] + m[1][0] * m[2][2] * m[3][1] + 
                   m[2][0] * m[1][1] * m[3][2] - m[2][0] * m[1][2] * m[3][1] - 
                   m[3][0] * m[1][1] * m[2][2] + m[3][0] * m[1][2] * m[2][1];

    inv.m[0][1] = -m[0][1] * m[2][2] * m[3][3] + m[0][1] * m[2][3] * m[3][2] + 
                   m[2][1] * m[0][2] * m[3][3] - m[2][1] * m[0][3] * m[3][2] - 
                   m[3][1] * m[0][2] * m[2][3] + m[3][1] * m[0][3] * m[2][2];

    inv.m[1][1] = m[0][0] * m[2][2] * m[3][3] - m[0][0] * m[2][3] * m[3][2] - 
                  m[2][0] * m[0][2] * m[3][3] + m[2][0] * m[0][3] * m[3][2] + 
                  m[3][0] * m[0][2] * m[2][3] - m[3][0] * m[0][3] * m[2][2];

    inv.m[2][1] = -m[0][0] * m[2][1] * m[3][3] + m[0][0] * m[2][3] * m[3][1] + 
                   m[2][0] * m[0][1] * m[3][3] - m[2][0] * m[0][3] * m[3][1] - 
                   m[3][0] * m[0][1] * m[2][3] + m[3][0] * m[0][3] * m[2][1];

    inv.m[3][1] = m[0][0] * m[2][1] * m[3][2] - m[0][0] * m[2][2] * m[3][1] - 
                  m[2][0] * m[0][1] * m[3][2] + m[2][0] * m[0][2] * m[3][1] + 
                  m[3][0] * m[0][1] * m[2][2] - m[3][0] * m[0][2] * m[2][1];

    inv.m[0][2] = m[0][1] * m[1][2] * m[3][3] - m[0][1] * m[1][3] * m[3][2] - 
                  m[1][1] * m[0][2] * m[3][3] + m[1][1] * m[0][3] * m[3][2] + 
                  m[3][1] * m[0][2] * m[1][3] - m[3][1] * m[0][3] * m[1][2];

    inv.m[1][2] = -m[0][0] * m[1][2] * m[3][3] + m[0][0] * m[1][3] * m[3][2] + 
                   m[1][0] * m[0][2] * m[3][3] - m[1][0] * m[0][3] * m[3][2] - 
                   m[3][0] * m[0][2] * m[1][3] + m[3][0] * m[0][3] * m[1][2];

    inv.m[2][2] = m[0][0] * m[1][1] * m[3][3] - m[0][0] * m[1][3] * m[3][1] - 
                  m[1][0] * m[0][1] * m[3][3] + m[1][0] * m[0][3] * m[3][1] + 
                  m[3][0] * m[0][1] * m[1][3] - m[3][0] * m[0][3] * m[1][1];

    inv.m[3][2] = -m[0][0] * m[1][1] * m[3][2] + m[0][0] * m[1][2] * m[3][1] + 
                   m[1][0] * m[0][1] * m[3][2] - m[1][0] * m[0][2] * m[3][1] - 
                   m[3][0] * m[0][1] * m[1][2] + m[3][0] * m[0][2] * m[1][1];

    inv.m[0][3] = -m[0][1] * m[1][2] * m[2][3] + m[0][1] * m[1][3] * m[2][2] + 
                   m[1][1] * m[0][2] * m[2][3] - m[1][1] * m[0][3] * m[2][2] - 
                   m[2][1] * m[0][2] * m[1][3] + m[2][1] * m[0][3] * m[1][2];

    inv.m[1][3] = m[0][0] * m[1][2] * m[2][3] - m[0][0] * m[1][3] * m[2][2] - 
                  m[1][0] * m[0][2] * m[2][3] + m[1][0] * m[0][3] * m[2][2] + 
                  m[2][0] * m[0][2] * m[1][3] - m[2][0] * m[0][3] * m[1][2];

    inv.m[2][3] = -m[0][0] * m[1][1] * m[2][3] + m[0][0] * m[1][3] * m[2][1] + 
                   m[1][0] * m[0][1] * m[2][3] - m[1][0] * m[0][3] * m[2][1] - 
                   m[2][0] * m[0][1] * m[1][3] + m[2][0] * m[0][3] * m[1][1];

    inv.m[3][3] = m[0][0] * m[1][1] * m[2][2] - m[0][0] * m[1][2] * m[2][1] - 
                  m[1][0] * m[0][1] * m[2][2] + m[1][0] * m[0][2] * m[2][1] + 
                  m[2][0] * m[0][1] * m[1][2] - m[2][0] * m[0][2] * m[1][1];

    // Calculating determinant
    det = m[0][0] * inv.m[0][0] + m[0][1] * inv.m[1][0] + 
          m[0][2] * inv.m[2][0] + m[0][3] * inv.m[3][0];

    // Check for degenerate matrix
    if (det == 0) {
        return Matrix4x4<T>(); 
    }

    det = 1 / det;

    // Multiply by inverse determinant
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            inv.m[i][j] *= det;
        }
    }

    return inv;
}

template<typename T>
Matrix4x4<T> Matrix4x4<T>::transposed() const {
    Matrix4x4<T> result;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            result.m[i][j] = m[j][i];
        }
    }
    return result;
}

template<typename T>
T* Matrix4x4<T>::operator[](int row) {
    return m[row];
}

template<typename T>
const T* Matrix4x4<T>::operator[](int row) const {
    return m[row];
}

template<typename T>
T& Matrix4x4<T>::operator()(int row, int col) {
    return m[row][col];
}

template<typename T>
const T& Matrix4x4<T>::operator()(int row, int col) const {
    return m[row][col];
}

template<typename T>
bool Matrix4x4<T>::operator==(const Matrix4x4<T>& other) const {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (m[i][j] != other.m[i][j]) return false;
        }
    }
    return true;
}

// Explicit template instantiations
template class Matrix4x4<float>;
template class Matrix4x4<int>;
template class Matrix4x4<double>;