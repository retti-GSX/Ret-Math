#include "../../include/quaternions/quaternion.hpp"

// Constructors

template<typename T>
Quaternion<T>::Quaternion(T w, T x, T y, T z) : w(w), x(x), y(y), z(z) {}

template<typename T>
Quaternion<T>::Quaternion(const Vector3<T>& axis, T angle) {
    T halfAngle = angle / static_cast<T>(2);
    T sinHalfAngle = static_cast<T>(std::sin(halfAngle));
    Vector3<T> normalizedAxis = axis.normalized();
    w = static_cast<T>(std::cos(halfAngle));
    x = normalizedAxis.x * sinHalfAngle;
    y = normalizedAxis.y * sinHalfAngle;
    z = normalizedAxis.z * sinHalfAngle;
}

// Normalization

template<typename T>
Quaternion<T> Quaternion<T>::normalized() const {
    T len = static_cast<T>(std::sqrt(w * w + x * x + y * y + z * z));
    if (len > 0) {
        return Quaternion<T>(w / len, x / len, y / len, z / len);
    }
    return Quaternion<T>(1, 0, 0, 0);
}

template<typename T>
void Quaternion<T>::normalize() {
    T len = static_cast<T>(std::sqrt(w * w + x * x + y * y + z * z));
    if (len > 0) {
        w /= len;
        x /= len;
        y /= len;
        z /= len;
    }
}

// Inverse

template<typename T>
Quaternion<T> Quaternion<T>::conjugate() const {
    return Quaternion<T>(w, -x, -y, -z);
}

template<typename T>
Quaternion<T> Quaternion<T>::inverse() const {
    T lenSq = w * w + x * x + y * y + z * z;
    if (lenSq == 0) {
        return Quaternion<T>();
    }
    T invLenSq = 1 / lenSq;
    return Quaternion<T>(w * invLenSq, -x * invLenSq, -y * invLenSq, -z * invLenSq);
}

// Multiplication

template<typename T>
Quaternion<T> Quaternion<T>::operator*(const Quaternion<T>& other) const {
    return Quaternion<T>(
        w * other.w - x * other.x - y * other.y - z * other.z,
        w * other.x + x * other.w + y * other.z - z * other.y,
        w * other.y - x * other.z + y * other.w + z * other.x,
        w * other.z + x * other.y - y * other.x + z * other.w
    );
}

template<typename T>
Vector3<T> Quaternion<T>::operator*(const Vector3<T>& vec) const {
    Quaternion<T> vecQuat(0, vec.x, vec.y, vec.z);
    Quaternion<T> conj = conjugate();
    Quaternion<T> result = (*this) * vecQuat * conj;
    return Vector3<T>(result.x, result.y, result.z);
}

// Interpolation

template<typename T>
Quaternion<T> Quaternion<T>::lerp(const Quaternion<T>& a, const Quaternion<T>& b, T t) {
    return Quaternion<T>(
        a.w + (b.w - a.w) * t,
        a.x + (b.x - a.x) * t,
        a.y + (b.y - a.y) * t,
        a.z + (b.z - a.z) * t
    ).normalized();
}

template<typename T>
Quaternion<T> Quaternion<T>::slerp(const Quaternion<T>& a, const Quaternion<T>& b, T t) {
    T dot = a.w * b.w + a.x * b.x + a.y * b.y + a.z * b.z;
    
    Quaternion<T> bQuat = b;
    if (dot < 0) {
        bQuat = Quaternion<T>(-b.w, -b.x, -b.y, -b.z);
        dot = -dot;
    }
    
    const T DOT_THRESHOLD = static_cast<T>(0.9995);
    if (dot > DOT_THRESHOLD) {
        return lerp(a, bQuat, t).normalized();
    }
    
    T theta_0 = static_cast<T>(std::acos(dot));
    T theta = theta_0 * t;
    T sin_theta = static_cast<T>(std::sin(theta));
    T sin_theta_0 = static_cast<T>(std::sin(theta_0));
    
    T s0 = static_cast<T>(std::cos(theta)) - dot * sin_theta / sin_theta_0;
    T s1 = sin_theta / sin_theta_0;
    
    return Quaternion<T>(
        s0 * a.w + s1 * bQuat.w,
        s0 * a.x + s1 * bQuat.x,
        s0 * a.y + s1 * bQuat.y,
        s0 * a.z + s1 * bQuat.z
    ).normalized();
}

// Transformations

template<typename T>
Matrix4x4<T> Quaternion<T>::toMatrix() const {
    T xx = x * x, yy = y * y, zz = z * z;
    T xy = x * y, xz = x * z, yz = y * z;
    T wx = w * x, wy = w * y, wz = w * z;
    
    Matrix4x4<T> result;
    result[0][0] = 1 - 2 * (yy + zz);
    result[0][1] = 2 * (xy - wz);
    result[0][2] = 2 * (xz + wy);
    result[0][3] = 0;
    
    result[1][0] = 2 * (xy + wz);
    result[1][1] = 1 - 2 * (xx + zz);
    result[1][2] = 2 * (yz - wx);
    result[1][3] = 0;
    
    result[2][0] = 2 * (xz - wy);
    result[2][1] = 2 * (yz + wx);
    result[2][2] = 1 - 2 * (xx + yy);
    result[2][3] = 0;
    
    result[3][0] = 0;
    result[3][1] = 0;
    result[3][2] = 0;
    result[3][3] = 1;
    
    return result;
}

template<typename T>
Quaternion<T> Quaternion<T>::fromMatrix(const Matrix4x4<T>& mat) {
    T trace = mat[0][0] + mat[1][1] + mat[2][2];
    
    if (trace > 0) {
        T s = static_cast<T>(std::sqrt(trace + 1)) * 2;
        return Quaternion<T>(
            s / 4,
            (mat[2][1] - mat[1][2]) / s,
            (mat[0][2] - mat[2][0]) / s,
            (mat[1][0] - mat[0][1]) / s
        );
    } else if (mat[0][0] > mat[1][1] && mat[0][0] > mat[2][2]) {
        T s = static_cast<T>(std::sqrt(1 + mat[0][0] - mat[1][1] - mat[2][2])) * 2;
        return Quaternion<T>(
            (mat[2][1] - mat[1][2]) / s,
            s / 4,
            (mat[1][0] + mat[0][1]) / s,
            (mat[0][2] + mat[2][0]) / s
        );
    } else if (mat[1][1] > mat[2][2]) {
        T s = static_cast<T>(std::sqrt(1 + mat[1][1] - mat[0][0] - mat[2][2])) * 2;
        return Quaternion<T>(
            (mat[0][2] - mat[2][0]) / s,
            (mat[1][0] + mat[0][1]) / s,
            s / 4,
            (mat[2][1] + mat[1][2]) / s
        );
    } else {
        T s = static_cast<T>(std::sqrt(1 + mat[2][2] - mat[0][0] - mat[1][1])) * 2;
        return Quaternion<T>(
            (mat[1][0] - mat[0][1]) / s,
            (mat[0][2] + mat[2][0]) / s,
            (mat[2][1] + mat[1][2]) / s,
            s / 4
        );
    }
}

// Axis and angle

template<typename T>
void Quaternion<T>::toAxisAngle(Vector3<T>& axis, T& angle) const {
    Quaternion<T> q = normalized();
    angle = static_cast<T>(2 * std::acos(q.w));
    T s = static_cast<T>(std::sqrt(1 - q.w * q.w));
    if (s < static_cast<T>(0.001)) {
        axis = Vector3<T>(1, 0, 0);
    } else {
        axis = Vector3<T>(q.x / s, q.y / s, q.z / s);
    }
}

template<typename T>
Quaternion<T> Quaternion<T>::fromAxisAngle(const Vector3<T>& axis, T angle) {
    return Quaternion<T>(axis, angle);
}

// Euler angles

template<typename T>
Quaternion<T> Quaternion<T>::fromEuler(T pitch, T yaw, T roll) {
    T cy = static_cast<T>(std::cos(yaw * 0.5));
    T sy = static_cast<T>(std::sin(yaw * 0.5));
    T cp = static_cast<T>(std::cos(pitch * 0.5));
    T sp = static_cast<T>(std::sin(pitch * 0.5));
    T cr = static_cast<T>(std::cos(roll * 0.5));
    T sr = static_cast<T>(std::sin(roll * 0.5));
    
    return Quaternion<T>(
        cy * cp * cr + sy * sp * sr,
        sy * cp * cr - cy * sp * sr,
        cy * sp * cr + sy * cp * sr,
        cy * cp * sr - sy * sp * cr
    );
}

template<typename T>
Vector3<T> Quaternion<T>::toEuler() const {
    Quaternion<T> q = normalized();

    T sinr_cosp = 2 * (q.w * q.x + q.y * q.z);
    T cosr_cosp = 1 - 2 * (q.x * q.x + q.y * q.y);
    T roll = static_cast<T>(std::atan2(sinr_cosp, cosr_cosp));

    T sinp = 2 * (q.w * q.y - q.z * q.x);
    T pitch;
    if (std::abs(sinp) >= 1) {
        pitch = static_cast<T>(std::copysign(3.14159265358979323846 / 2, sinp));
    } else {
        pitch = static_cast<T>(std::asin(sinp));
    }

    T siny_cosp = 2 * (q.w * q.z + q.x * q.y);
    T cosy_cosp = 1 - 2 * (q.y * q.y + q.z * q.z);
    T yaw = static_cast<T>(std::atan2(siny_cosp, cosy_cosp));

    return Vector3<T>(pitch, yaw, roll);
}

// Explicit template instantiations
template class Quaternion<float>;
template class Quaternion<double>;
