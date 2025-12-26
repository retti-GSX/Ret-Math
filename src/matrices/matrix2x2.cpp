#include "../../include/matrices/matrix2x2.hpp"

// Constructors

template<typename T>
Matrix2x2<T>::Matrix2x2() {
    m[0][0] = 1; m[0][1] = 0;
    m[1][0] = 0; m[1][1] = 1;
}

template<typename T>
Matrix2x2<T>::Matrix2x2(T identity) {
    m[0][0] = identity; m[0][1] = 0;
    m[1][0] = 0; m[1][1] = identity;
}

template<typename T>
Matrix2x2<T>::Matrix2x2(T m00, T m01, T m10, T m11) {
    m[0][0] = m00; m[0][1] = m01;
    m[1][0] = m10; m[1][1] = m11;
}

// Static methods

template<typename T>
Matrix2x2<T> Matrix2x2<T>::identity() {
    return Matrix2x2<T>(1, 0, 0, 1);
}

template<typename T>
Matrix2x2<T> Matrix2x2<T>::rotation(T angle) {
    T cosAngle = std::cos(angle);
    T sinAngle = std::sin(angle);
    return Matrix2x2<T>(cosAngle, -sinAngle, sinAngle, cosAngle);
}

template<typename T>
Matrix2x2<T> Matrix2x2<T>::scale(T sx, T sy) {
    return Matrix2x2<T>(sx, 0, 0, sy);
}

template<typename T>
Matrix2x2<T> Matrix2x2<T>::scale(T s) {
    return Matrix2x2<T>(s, 0, 0, s);
}

template<typename T>
Matrix2x2<T> Matrix2x2<T>::shearX(T factor) {
    return Matrix2x2<T>(1, factor, 0, 1);
}

template<typename T>
Matrix2x2<T> Matrix2x2<T>::shearY(T factor) {
    return Matrix2x2<T>(1, 0, factor, 1);
}

// Operator overloads

template<typename T>
Matrix2x2<T> Matrix2x2<T>::operator+(const Matrix2x2<T>& other) const {
    return Matrix2x2<T>(
        m[0][0] + other.m[0][0], m[0][1] + other.m[0][1],
        m[1][0] + other.m[1][0], m[1][1] + other.m[1][1]
    );
}

template<typename T>
Matrix2x2<T> Matrix2x2<T>::operator-(const Matrix2x2<T>& other) const {
    return Matrix2x2<T>(
        m[0][0] - other.m[0][0], m[0][1] - other.m[0][1],
        m[1][0] - other.m[1][0], m[1][1] - other.m[1][1]
    );
}

template<typename T>
Matrix2x2<T> Matrix2x2<T>::operator*(const Matrix2x2<T>& other) const {
    return Matrix2x2<T>(
        m[0][0] * other.m[0][0] + m[0][1] * other.m[1][0],
        m[0][0] * other.m[0][1] + m[0][1] * other.m[1][1],
        m[1][0] * other.m[0][0] + m[1][1] * other.m[1][0],
        m[1][0] * other.m[0][1] + m[1][1] * other.m[1][1]
    );
}

template<typename T>
Matrix2x2<T> Matrix2x2<T>::operator*(T scalar) const {
    return Matrix2x2<T>(
        m[0][0] * scalar, m[0][1] * scalar,
        m[1][0] * scalar, m[1][1] * scalar
    );
}

template<typename T>
Vector2<T> Matrix2x2<T>::operator*(const Vector2<T>& vec) const {
    return Vector2<T>(
        m[0][0] * vec.x + m[0][1] * vec.y,
        m[1][0] * vec.x + m[1][1] * vec.y
    );
}

// Matrix operations

template<typename T>
Matrix2x2<T> Matrix2x2<T>::inverse() const {
    T det = determinant();
    if (det == 0) {
        return Matrix2x2<T>();
    }
    T invDet = 1.0f / det;
    return Matrix2x2<T>(
        m[1][1] * invDet, -m[0][1] * invDet,
        -m[1][0] * invDet, m[0][0] * invDet
    );
}

template<typename T>
Matrix2x2<T> Matrix2x2<T>::transposed() const {
    return Matrix2x2<T>(m[0][0], m[1][0], m[0][1], m[1][1]);
}

template<typename T>
T Matrix2x2<T>::determinant() const {
    return m[0][0] * m[1][1] - m[0][1] * m[1][0];
}

template<typename T>
T Matrix2x2<T>::trace() const {
    return m[0][0] + m[1][1];
}

template<typename T>
Matrix2x2<T> Matrix2x2<T>::diagonal(T d1, T d2) {
    return Matrix2x2<T>(d1, 0, 0, d2);
}

template<typename T>
T& Matrix2x2<T>::operator()(int row, int col) {
    return m[row][col];
}

template<typename T>
const T& Matrix2x2<T>::operator()(int row, int col) const {
    return m[row][col];
}

template<typename T>
Vector2<T> Matrix2x2<T>::getRow(int row) const {
    return Vector2<T>(m[row][0], m[row][1]);
}

template<typename T>
Vector2<T> Matrix2x2<T>::getColumn(int col) const {
    return Vector2<T>(m[0][col], m[1][col]);
}

template<typename T>
bool Matrix2x2<T>::operator==(const Matrix2x2<T>& other) const {
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            if (m[i][j] != other.m[i][j]) return false;
        }
    }
    return true;
}

template<typename T>
bool Matrix2x2<T>::isOrthogonal() const {
    Matrix2x2<T> transposedMat = transposed();
    Matrix2x2<T> product = (*this) * transposedMat;
    Matrix2x2<T> identityMat = Matrix2x2<T>::identity();
    return product == identityMat;
}

template<typename T>
Vector2<T> Matrix2x2<T>::rotateVector(const Vector2<T>& vec, T angle) {
    Matrix2x2<T> rotMat = rotation(angle);
    return rotMat * vec;
}

// Explicit template instantiations
template class Matrix2x2<float>;
template class Matrix2x2<int>;
template class Matrix2x2<double>;
