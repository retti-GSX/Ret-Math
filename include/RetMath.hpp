#pragma once

// Mathematical constants and functions
namespace MathConstants {
    constexpr float PI = 3.14159265358979323846f;
    constexpr float PI_2 = 1.57079632679489661923f;
    constexpr float PI_4 = 0.785398163397448309616f;
    constexpr float TAU = 6.28318530717958647692f;
    constexpr float E = 2.71828182845904523536f;
    constexpr float SQRT2 = 1.41421356237309504880f;
    constexpr float SQRT3 = 1.73205080756887729352f;
    constexpr float DEG_TO_RAD = PI / 180.0f;
    constexpr float RAD_TO_DEG = 180.0f / PI;
    constexpr float EPSILON = 1e-6f;
    constexpr float EPSILON_LOW = 1e-3f;
    constexpr float EPSILON_HIGH = 1e-9f;
}

// Vectors
#include "vectors/vector2.hpp"
#include "vectors/vector3.hpp"
#include "vectors/vector4.hpp"

// Matrices
#include "matrices/matrix2x2.hpp"
#include "matrices/matrix3x3.hpp"
#include "matrices/matrix4x4.hpp"

// Quaternions
#include "quaternions/quaternion.hpp"

// Geometry
#include "geometry/plane.hpp"
#include "geometry/ray.hpp"
#include "geometry/rect.hpp"
#include "geometry/circle.hpp"
#include "geometry/aabb.hpp"

// Transformations
#include "transformations/transform.hpp"

// Color
#include "color/color.hpp"

// Utilities
#include "utilities/random.hpp"
#include "utilities/interpolation.hpp"
#include "utilities/intersection.hpp"

// Aliases for commonly used types
using Vec2 = Vector2<float>;
using Vec3 = Vector3<float>;
using Vec4 = Vector4<float>;
using Mat2 = Matrix2x2<float>;
using Mat3 = Matrix3x3<float>;
using Mat4 = Matrix4x4<float>;
using Quat = Quaternion<float>;
using Rectf = Rect<float>;
using Circlef = Circle<float>;
using AABBf = AABB<float>;
using Color = ::Color;

// Namespace for mathematical utilities
namespace Math {
    using namespace MathConstants;
    
    template<typename T>
    inline T toRadians(T degrees) {
        return degrees * static_cast<T>(DEG_TO_RAD);
    }
    
    template<typename T>
    inline T toDegrees(T radians) {
        return radians * static_cast<T>(RAD_TO_DEG);
    }
    
    template<typename T>
    inline T clamp(T value, T min, T max) {
        return (value < min) ? min : (value > max) ? max : value;
    }
    
    template<typename T>
    inline T clamp01(T value) {
        return clamp(value, T(0), T(1));
    }
    
    template<typename T>
    inline T lerp(T a, T b, T t) {
        return a + (b - a) * t;
    }
    
    template<typename T>
    inline T inverseLerp(T a, T b, T value) {
        return (value - a) / (b - a);
    }
    
    template<typename T>
    inline T smoothstep(T edge0, T edge1, T x) {
        x = clamp((x - edge0) / (edge1 - edge0), T(0), T(1));
        return x * x * (T(3) - T(2) * x);
    }
    
    template<typename T>
    inline T smootherstep(T edge0, T edge1, T x) {
        x = clamp((x - edge0) / (edge1 - edge0), T(0), T(1));
        return x * x * x * (x * (x * T(6) - T(15)) + T(10));
    }
    
    inline bool approximately(float a, float b, float epsilon = 1e-6f) {
        return std::abs(a - b) <= epsilon;
    }
    
    inline bool approximately(double a, double b, double epsilon = 1e-9) {
        return std::abs(a - b) <= epsilon;
    }
    
    template<typename T>
    inline T min(T a, T b) {
        return a < b ? a : b;
    }
    
    template<typename T>
    inline T max(T a, T b) {
        return a > b ? a : b;
    }
    
    template<typename T>
    inline T abs(T value) {
        return value < T(0) ? -value : value;
    }
    
    template<typename T>
    inline T sign(T value) {
        return value > T(0) ? T(1) : (value < T(0) ? T(-1) : T(0));
    }
    
    inline float floor(float value) { return std::floor(value); }
    inline float ceil(float value) { return std::ceil(value); }
    inline float round(float value) { return std::round(value); }
    inline float sqrt(float value) { return std::sqrt(value); }
    inline float pow(float base, float exponent) { return std::pow(base, exponent); }
    inline float sin(float angle) { return std::sin(angle); }
    inline float cos(float angle) { return std::cos(angle); }
    inline float tan(float angle) { return std::tan(angle); }
    inline float asin(float value) { return std::asin(value); }
    inline float acos(float value) { return std::acos(value); }
    inline float atan(float value) { return std::atan(value); }
    inline float atan2(float y, float x) { return std::atan2(y, x); }
    inline float exp(float value) { return std::exp(value); }
    inline float log(float value) { return std::log(value); }
    inline float log10(float value) { return std::log10(value); }
    
    inline int floorToInt(float value) { return static_cast<int>(std::floor(value)); }
    inline int ceilToInt(float value) { return static_cast<int>(std::ceil(value)); }
    inline int roundToInt(float value) { return static_cast<int>(std::round(value)); }
    
    template<typename T>
    inline T mod(T a, T b) {
        return a - b * floor(a / b);
    }
    
    inline float repeat(float t, float length) {
        return t - floor(t / length) * length;
    }
    
    inline float pingPong(float t, float length) {
        t = repeat(t, length * 2.0f);
        return length - abs(t - length);
    }
}
