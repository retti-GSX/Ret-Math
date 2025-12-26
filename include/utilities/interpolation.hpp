#pragma once
#include <cmath>
#include <functional>
#include <vector>
#include "../vectors/vector2.hpp"
#include "../vectors/vector3.hpp"
#include "../vectors/vector4.hpp"
#include "../quaternions/quaternion.hpp"

namespace Interpolation {
    template<typename T>
    T lerp(const T& a, const T& b, float t);
    
    template<typename T>
    Quaternion<T> slerp(const Quaternion<T>& a, const Quaternion<T>& b, float t);
    
    enum class EaseType {
        Linear,
        SineIn,
        SineOut,
        SineInOut,
        QuadIn,
        QuadOut,
        QuadInOut,
        CubicIn,
        CubicOut,
        CubicInOut,
        QuartIn,
        QuartOut,
        QuartInOut,
        QuintIn,
        QuintOut,
        QuintInOut,
        ExpoIn,
        ExpoOut,
        ExpoInOut,
        CircIn,
        CircOut,
        CircInOut,
        BackIn,
        BackOut,
        BackInOut,
        ElasticIn,
        ElasticOut,
        ElasticInOut,
        BounceIn,
        BounceOut,
        BounceInOut
    };
    
    namespace EaseFunctions {
        float linear(float t);
        float sineIn(float t);
        float sineOut(float t);
        float sineInOut(float t);
        float quadIn(float t);
        float quadOut(float t);
        float quadInOut(float t);
        float cubicIn(float t);
        float cubicOut(float t);
        float cubicInOut(float t);
        float quartIn(float t);
        float quartOut(float t);
        float quartInOut(float t);
        float quintIn(float t);
        float quintOut(float t);
        float quintInOut(float t);
        float expoIn(float t);
        float expoOut(float t);
        float expoInOut(float t);
        float circIn(float t);
        float circOut(float t);
        float circInOut(float t);
        float backIn(float t);
        float backOut(float t);
        float backInOut(float t);
        float elasticIn(float t);
        float elasticOut(float t);
        float elasticInOut(float t);
        float bounceOut(float t);
        float bounceIn(float t);
        float bounceInOut(float t);
    }
    
    float ease(float t, EaseType type = EaseType::Linear);
    
    template<typename T>
    T easeLerp(const T& a, const T& b, float t, EaseType type = EaseType::Linear);
    
    template<typename T>
    T cubicInterpolate(const T& p0, const T& p1, const T& p2, const T& p3, float t);
    
    template<typename T>
    T bilinearInterpolate(const T& v00, const T& v10, const T& v01, const T& v11,
                          float tx, float ty);
    
    template<typename T>
    T trilinearInterpolate(const T& v000, const T& v100, const T& v010, const T& v110,
                           const T& v001, const T& v101, const T& v011, const T& v111,
                           float tx, float ty, float tz);
    
    template<typename T>
    T bezier(const T& p0, const T& p1, const T& p2, float t);
    
    template<typename T>
    T bezier(const T& p0, const T& p1, const T& p2, const T& p3, float t);
    
    template<typename T>
    T pathInterpolate(const std::vector<T>& points, float t);
}
