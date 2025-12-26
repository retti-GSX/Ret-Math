#include "../../include/matrices/matrix3x3.hpp"
#include "../../include/matrices/matrix4x4.hpp"

// Constructors

template<typename T>
Matrix3x3<T>::Matrix3x3() {
    m[0][0] = 1; m[0][1] = 0; m[0][2] = 0;
    m[1][0] = 0; m[1][1] = 1; m[1][2] = 0;
    m[2][0] = 0; m[2][1] = 0; m[2][2] = 1;
}

template<typename T>
Matrix3x3<T>::Matrix3x3(T identity) {
    m[0][0] = identity; m[0][1] = 0; m[0][2] = 0;
    m[1][0] = 0; m[1][1] = identity; m[1][2] = 0;
    m[2][0] = 0; m[2][1] = 0; m[2][2] = identity;
}

template<typename T>
Matrix3x3<T>::Matrix3x3(T m00, T m01, T m02,
                       T m10, T m11, T m12,
                       T m20, T m21, T m22) {
    m[0][0] = m00; m[0][1] = m01; m[0][2] = m02;
    m[1][0] = m10; m[1][1] = m11; m[1][2] = m12;
    m[2][0] = m20; m[2][1] = m21; m[2][2] = m22;
}

// Static methods

template<typename T>
Matrix3x3<T> Matrix3x3<T>::identity() {
    return Matrix3x3<T>(1, 0, 0, 0, 1, 0, 0, 0, 1);
}

template<typename T>
Matrix3x3<T> Matrix3x3<T>::translation(T x, T y) {
    return Matrix3x3<T>(1, 0, x, 0, 1, y, 0, 0, 1);
}

template<typename T>
Matrix3x3<T> Matrix3x3<T>::translation(const Vector2<T>& vec) {
    return translation(vec.x, vec.y);
}

template<typename T>
Matrix3x3<T> Matrix3x3<T>::rotation(T angle) {
    T cosAngle = static_cast<T>(std::cos(angle));
    T sinAngle = static_cast<T>(std::sin(angle));
    return Matrix3x3<T>(cosAngle, -sinAngle, 0, sinAngle, cosAngle, 0, 0, 0, 1);
}

template<typename T>
Matrix3x3<T> Matrix3x3<T>::rotationX(T angle) {
    T cosAngle = static_cast<T>(std::cos(angle));
    T sinAngle = static_cast<T>(std::sin(angle));
    return Matrix3x3<T>(1, 0, 0, 0, cosAngle, -sinAngle, 0, sinAngle, cosAngle);
}

template<typename T>
Matrix3x3<T> Matrix3x3<T>::rotationY(T angle) {
    T cosAngle = static_cast<T>(std::cos(angle));
    T sinAngle = static_cast<T>(std::sin(angle));
    return Matrix3x3<T>(cosAngle, 0, sinAngle, 0, 1, 0, -sinAngle, 0, cosAngle);
}

template<typename T>
Matrix3x3<T> Matrix3x3<T>::rotationZ(T angle) {
    T cosAngle = static_cast<T>(std::cos(angle));
    T sinAngle = static_cast<T>(std::sin(angle));
    return Matrix3x3<T>(cosAngle, -sinAngle, 0, sinAngle, cosAngle, 0, 0, 0, 1);
}

template<typename T>
Matrix3x3<T> Matrix3x3<T>::scale(T sx, T sy, T sz) {
    return Matrix3x3<T>(sx, 0, 0, 0, sy, 0, 0, 0, sz);
}

template<typename T>
Matrix3x3<T> Matrix3x3<T>::scale(T s) {
    return Matrix3x3<T>(s, 0, 0, 0, s, 0, 0, 0, s);
}

template<typename T>
Matrix3x3<T> Matrix3x3<T>::scale(const Vector3<T>& scale) {
    return Matrix3x3<T>(scale.x, 0, 0, 0, scale.y, 0, 0, 0, scale.z);
}

template<typename T>
Matrix3x3<T> Matrix3x3<T>::fromMatrix2x2(const Matrix2x2<T>& mat2) {
    return Matrix3x3<T>(mat2(0, 0), mat2(0, 1), 0, mat2(1, 0), mat2(1, 1), 0, 0, 0, 1);
}

// Operator overloads

template<typename T>
Matrix3x3<T> Matrix3x3<T>::operator+(const Matrix3x3<T>& other) const {
    return Matrix3x3<T>(
        m[0][0] + other.m[0][0], m[0][1] + other.m[0][1], m[0][2] + other.m[0][2],
        m[1][0] + other.m[1][0], m[1][1] + other.m[1][1], m[1][2] + other.m[1][2],
        m[2][0] + other.m[2][0], m[2][1] + other.m[2][1], m[2][2] + other.m[2][2]
    );
}

template<typename T>
Matrix3x3<T> Matrix3x3<T>::operator-(const Matrix3x3<T>& other) const {
    return Matrix3x3<T>(
        m[0][0] - other.m[0][0], m[0][1] - other.m[0][1], m[0][2] - other.m[0][2],
        m[1][0] - other.m[1][0], m[1][1] - other.m[1][1], m[1][2] - other.m[1][2],
        m[2][0] - other.m[2][0], m[2][1] - other.m[2][1], m[2][2] - other.m[2][2]
    );
}

template<typename T>
Matrix3x3<T> Matrix3x3<T>::operator*(const Matrix3x3<T>& other) const {
    return Matrix3x3<T>(
        m[0][0] * other.m[0][0] + m[0][1] * other.m[1][0] + m[0][2] * other.m[2][0],
        m[0][0] * other.m[0][1] + m[0][1] * other.m[1][1] + m[0][2] * other.m[2][1],
        m[0][0] * other.m[0][2] + m[0][1] * other.m[1][2] + m[0][2] * other.m[2][2],
        m[1][0] * other.m[0][0] + m[1][1] * other.m[1][0] + m[1][2] * other.m[2][0],
        m[1][0] * other.m[0][1] + m[1][1] * other.m[1][1] + m[1][2] * other.m[2][1],
        m[1][0] * other.m[0][2] + m[1][1] * other.m[1][2] + m[1][2] * other.m[2][2],
        m[2][0] * other.m[0][0] + m[2][1] * other.m[1][0] + m[2][2] * other.m[2][0],
        m[2][0] * other.m[0][1] + m[2][1] * other.m[1][1] + m[2][2] * other.m[2][1],
        m[2][0] * other.m[0][2] + m[2][1] * other.m[1][2] + m[2][2] * other.m[2][2]
    );
}

template<typename T>
Matrix3x3<T> Matrix3x3<T>::operator*(T scalar) const {
    return Matrix3x3<T>(
        m[0][0] * scalar, m[0][1] * scalar, m[0][2] * scalar,
        m[1][0] * scalar, m[1][1] * scalar, m[1][2] * scalar,
        m[2][0] * scalar, m[2][1] * scalar, m[2][2] * scalar
    );
}

template<typename T>
Vector3<T> Matrix3x3<T>::operator*(const Vector3<T>& vec) const {
    return Vector3<T>(
        m[0][0] * vec.x + m[0][1] * vec.y + m[0][2] * vec.z,
        m[1][0] * vec.x + m[1][1] * vec.y + m[1][2] * vec.z,
        m[2][0] * vec.x + m[2][1] * vec.y + m[2][2] * vec.z
    );
}

template<typename T>
Vector2<T> Matrix3x3<T>::transformPoint(const Vector2<T>& point) const {
    return Vector2<T>(
        m[0][0] * point.x + m[0][1] * point.y + m[0][2],
        m[1][0] * point.x + m[1][1] * point.y + m[1][2]
    );
}

template<typename T>
Vector2<T> Matrix3x3<T>::transformVector(const Vector2<T>& vector) const {
    return Vector2<T>(
        m[0][0] * vector.x + m[0][1] * vector.y,
        m[1][0] * vector.x + m[1][1] * vector.y
    );
}

// Matrix operations

template<typename T>
Matrix3x3<T> Matrix3x3<T>::inverse() const {
    T det = determinant();
    if (det == 0) {
        return Matrix3x3<T>();
    }
    T invDet = static_cast<T>(1.0) / det;
    return Matrix3x3<T>(
        (m[1][1] * m[2][2] - m[1][2] * m[2][1]) * invDet,
        (m[0][2] * m[2][1] - m[0][1] * m[2][2]) * invDet,
        (m[0][1] * m[1][2] - m[0][2] * m[1][1]) * invDet,
        (m[1][2] * m[2][0] - m[1][0] * m[2][2]) * invDet,
        (m[0][0] * m[2][2] - m[0][2] * m[2][0]) * invDet,
        (m[0][2] * m[1][0] - m[0][0] * m[1][2]) * invDet,
        (m[1][0] * m[2][1] - m[1][1] * m[2][0]) * invDet,
        (m[0][1] * m[2][0] - m[0][0] * m[2][1]) * invDet,
        (m[0][0] * m[1][1] - m[0][1] * m[1][0]) * invDet
    );
}

template<typename T>
Matrix3x3<T> Matrix3x3<T>::transposed() const {
    return Matrix3x3<T>(
        m[0][0], m[1][0], m[2][0],
        m[0][1], m[1][1], m[2][1],
        m[0][2], m[1][2], m[2][2]
    );
}

template<typename T>
T Matrix3x3<T>::determinant() const {
    return m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1]) -
           m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0]) +
           m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]);
}

template<typename T>
T Matrix3x3<T>::trace() const {
    return m[0][0] + m[1][1] + m[2][2];
}

template<typename T>
Matrix2x2<T> Matrix3x3<T>::submatrix(int excludedRow, int excludedCol) const {
    Matrix2x2<T> result;
    int rowOffset = 0;
    for (int i = 0; i < 3; ++i) {
        if (i == excludedRow) continue;
        int colOffset = 0;
        for (int j = 0; j < 3; ++j) {
            if (j == excludedCol) continue;
            result(rowOffset, colOffset) = m[i][j];
            colOffset++;
        }
        rowOffset++;
    }
    return result;
}

template<typename T>
T Matrix3x3<T>::minor(int row, int col) const {
    return submatrix(row, col).determinant();
}

template<typename T>
T Matrix3x3<T>::cofactor(int row, int col) const {
    T sign = static_cast<T>(((row + col) % 2 == 0) ? 1 : -1);  // Fixed: static_cast<T>()
    return sign * minor(row, col);
}

template<typename T>
T& Matrix3x3<T>::operator()(int row, int col) {
    return m[row][col];
}

template<typename T>
const T& Matrix3x3<T>::operator()(int row, int col) const {
    return m[row][col];
}

template<typename T>
Vector3<T> Matrix3x3<T>::getRow(int row) const {
    return Vector3<T>(m[row][0], m[row][1], m[row][2]);
}

template<typename T>
Vector3<T> Matrix3x3<T>::getColumn(int col) const {
    return Vector3<T>(m[0][col], m[1][col], m[2][col]);
}

template<typename T>
bool Matrix3x3<T>::operator==(const Matrix3x3<T>& other) const {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (m[i][j] != other.m[i][j]) return false;
        }
    }
    return true;
}

template<typename T>
bool Matrix3x3<T>::isOrthogonal() const {
    Matrix3x3<T> transposedMat = transposed();
    Matrix3x3<T> product = (*this) * transposedMat;
    Matrix3x3<T> identityMat = Matrix3x3<T>::identity();
    return product == identityMat;
}

template<typename T>
void Matrix3x3<T>::orthonormalize() {
    Vector3<T> x = getColumn(0);
    Vector3<T> y = getColumn(1);
    Vector3<T> z = getColumn(2);
    
    x.normalize();
    y = y - x * (x.dot(y));
    y.normalize();
    z = z - x * (x.dot(z)) - y * (y.dot(z));
    z.normalize();
    
    m[0][0] = x.x; m[1][0] = x.y; m[2][0] = x.z;
    m[0][1] = y.x; m[1][1] = y.y; m[2][1] = y.z;
    m[0][2] = z.x; m[1][2] = z.y; m[2][2] = z.z;
}

template<typename T>
Matrix3x3<T> Matrix3x3<T>::fromAxisAngle(const Vector3<T>& axis, T angle) {
    T cosAngle = static_cast<T>(std::cos(angle));
    T sinAngle = static_cast<T>(std::sin(angle));
    T oneMinusCos = 1 - cosAngle;
    
    Vector3<T> normalizedAxis = axis.normalized();
    T x = normalizedAxis.x;
    T y = normalizedAxis.y;
    T z = normalizedAxis.z;
    
    return Matrix3x3<T>(
        cosAngle + x * x * oneMinusCos, x * y * oneMinusCos - z * sinAngle, x * z * oneMinusCos + y * sinAngle,
        y * x * oneMinusCos + z * sinAngle, cosAngle + y * y * oneMinusCos, y * z * oneMinusCos - x * sinAngle,
        z * x * oneMinusCos - y * sinAngle, z * y * oneMinusCos + x * sinAngle, cosAngle + z * z * oneMinusCos
    );
}

template<typename T>
Matrix4x4<T> Matrix3x3<T>::toMatrix4x4() const {
    Matrix4x4<T> result;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            result.m[i][j] = m[i][j];  // Fixed: access to m[i][j] via field
        }
    }
    result.m[0][3] = 0;
    result.m[1][3] = 0;
    result.m[2][3] = 0;
    result.m[3][0] = 0;
    result.m[3][1] = 0;
    result.m[3][2] = 0;
    result.m[3][3] = 1;
    return result;
}

// Explicit template instantiations
template class Matrix3x3<float>;
template class Matrix3x3<int>;
template class Matrix3x3<double>;