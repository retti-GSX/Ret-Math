#include "../../include/utilities/interpolation.hpp"

namespace Interpolation {
    template<typename T>
    T lerp(const T& a, const T& b, float t) {
        return a + (b - a) * t;
    }
    
    template<typename T>
    Quaternion<T> slerp(const Quaternion<T>& a, const Quaternion<T>& b, float t) {
        return Quaternion<T>::slerp(a, b, t);
    }
    
    namespace EaseFunctions {
        float linear(float t) {
            return t;
        }
        
        float sineIn(float t) {
            return 1 - std::cos((t * 3.14159265358979323846f) / 2);
        }
        
        float sineOut(float t) {
            return std::sin((t * 3.14159265358979323846f) / 2);
        }
        
        float sineInOut(float t) {
            return -0.5f * (std::cos(3.14159265358979323846f * t) - 1);
        }
        
        float quadIn(float t) {
            return t * t;
        }
        
        float quadOut(float t) {
            return 1 - (1 - t) * (1 - t);
        }
        
        float quadInOut(float t) {
            return t < 0.5f ? 2 * t * t : 1 - static_cast<float>(std::pow(-2 * t + 2, 2)) / 2;
        }
        
        float cubicIn(float t) {
            return t * t * t;
        }
        
        float cubicOut(float t) {
            return 1 - static_cast<float>(std::pow(1 - t, 3));
        }
        
        float cubicInOut(float t) {
            return t < 0.5f ? 4 * t * t * t : 1 - static_cast<float>(std::pow(-2 * t + 2, 3)) / 2;
        }
        
        float quartIn(float t) {
            return t * t * t * t;
        }
        
        float quartOut(float t) {
            return 1 - static_cast<float>(std::pow(1 - t, 4));
        }
        
        float quartInOut(float t) {
            return t < 0.5f ? 8 * t * t * t * t : 1 - static_cast<float>(std::pow(-2 * t + 2, 4)) / 2;
        }
        
        float quintIn(float t) {
            return t * t * t * t * t;
        }
        
        float quintOut(float t) {
            return 1 - static_cast<float>(std::pow(1 - t, 5));
        }
        
        float quintInOut(float t) {
            return t < 0.5f ? 16 * t * t * t * t * t : 1 - static_cast<float>(std::pow(-2 * t + 2, 5)) / 2;
        }
        
        float expoIn(float t) {
            return t == 0 ? 0 : static_cast<float>(std::pow(2, 10 * t - 10));
        }
        
        float expoOut(float t) {
            return t == 1 ? 1 : 1 - static_cast<float>(std::pow(2, -10 * t));
        }
        
        float expoInOut(float t) {
            return t == 0 ? 0 : t == 1 ? 1 : t < 0.5f ? static_cast<float>(std::pow(2, 20 * t - 10)) / 2 : (2 - static_cast<float>(std::pow(2, -20 * t + 10))) / 2;
        }
        
        float circIn(float t) {
            return 1 - static_cast<float>(std::sqrt(1 - static_cast<float>(std::pow(t, 2))));
        }
        
        float circOut(float t) {
            return static_cast<float>(std::sqrt(1 - static_cast<float>(std::pow(t - 1, 2))));
        }
        
        float circInOut(float t) {
            return t < 0.5f ? (1 - static_cast<float>(std::sqrt(1 - static_cast<float>(std::pow(2 * t, 2))))) / 2 : (static_cast<float>(std::sqrt(1 - static_cast<float>(std::pow(-2 * t + 2, 2)))) + 1) / 2;
        }
        
        float backIn(float t) {
            const float c1 = 1.70158f;
            const float c3 = c1 + 1;
            return c3 * t * t * t - c1 * t * t;
        }
        
        float backOut(float t) {
            const float c1 = 1.70158f;
            const float c3 = c1 + 1;
            return 1 + c3 * static_cast<float>(std::pow(t - 1, 3)) + c1 * static_cast<float>(std::pow(t - 1, 2));
        }
        
        float backInOut(float t) {
            const float c1 = 1.70158f;
            const float c2 = c1 * 1.525f;
            return t < 0.5f ? (static_cast<float>(std::pow(2 * t, 2)) * ((c2 + 1) * 2 * t - c2)) / 2 : (static_cast<float>(std::pow(2 * t - 2, 2)) * ((c2 + 1) * (t * 2 - 2) + c2) + 2) / 2;
        }
        
        float elasticIn(float t) {
            const float c4 = (2 * 3.14159265358979323846f) / 3;
            return t == 0 ? 0 : t == 1 ? 1 : -static_cast<float>(std::pow(2, 10 * t - 10)) * static_cast<float>(std::sin((t * 10 - 10.75) * c4));
        }
        
        float elasticOut(float t) {
            const float c4 = (2 * 3.14159265358979323846f) / 3;
            return t == 0 ? 0 : t == 1 ? 1 : static_cast<float>(std::pow(2, -10 * t)) * static_cast<float>(std::sin((t * 10 - 0.75) * c4)) + 1;
        }
        
        float elasticInOut(float t) {
            const float c5 = static_cast<float>(2 * 3.14159265358979323846f / 4.5f);
            return t == 0 ? 0 : t == 1 ? 1 : t < 0.5f ? -(static_cast<float>(std::pow(2, 20 * t - 10)) * static_cast<float>(std::sin((20 * t - 11.125) * c5))) / 2 : (static_cast<float>(std::pow(2, -20 * t + 10)) * static_cast<float>(std::sin((20 * t - 11.125) * c5))) / 2 + 1;
        }
        
        float bounceOut(float t) {
            const float n1 = 7.5625;
            const float d1 = 2.75;
            if (t < 1.0f / d1) {
                return n1 * t * t;
            } else if (t < 2.0f / d1) {
                return n1 * (t -= 1.5f / d1) * t + 0.75f;
            } else if (t < 2.5f / d1) {
                return n1 * (t -= 2.25f / d1) * t + 0.9375f;
            } else {
                return n1 * (t -= 2.625f / d1) * t + 0.984375f;
            }
        }
        
        float bounceIn(float t) {
            return 1 - bounceOut(1 - t);
        }
        
        float bounceInOut(float t) {
            return t < 0.5f ? (1 - bounceOut(1 - 2 * t)) / 2 : (1 + bounceOut(2 * t - 1)) / 2;
        }
    }
    
    float ease(float t, EaseType type) {
        switch (type) {
            case EaseType::Linear: return EaseFunctions::linear(t);
            case EaseType::SineIn: return EaseFunctions::sineIn(t);
            case EaseType::SineOut: return EaseFunctions::sineOut(t);
            case EaseType::SineInOut: return EaseFunctions::sineInOut(t);
            case EaseType::QuadIn: return EaseFunctions::quadIn(t);
            case EaseType::QuadOut: return EaseFunctions::quadOut(t);
            case EaseType::QuadInOut: return EaseFunctions::quadInOut(t);
            case EaseType::CubicIn: return EaseFunctions::cubicIn(t);
            case EaseType::CubicOut: return EaseFunctions::cubicOut(t);
            case EaseType::CubicInOut: return EaseFunctions::cubicInOut(t);
            case EaseType::QuartIn: return EaseFunctions::quartIn(t);
            case EaseType::QuartOut: return EaseFunctions::quartOut(t);
            case EaseType::QuartInOut: return EaseFunctions::quartInOut(t);
            case EaseType::QuintIn: return EaseFunctions::quintIn(t);
            case EaseType::QuintOut: return EaseFunctions::quintOut(t);
            case EaseType::QuintInOut: return EaseFunctions::quintInOut(t);
            case EaseType::ExpoIn: return EaseFunctions::expoIn(t);
            case EaseType::ExpoOut: return EaseFunctions::expoOut(t);
            case EaseType::ExpoInOut: return EaseFunctions::expoInOut(t);
            case EaseType::CircIn: return EaseFunctions::circIn(t);
            case EaseType::CircOut: return EaseFunctions::circOut(t);
            case EaseType::CircInOut: return EaseFunctions::circInOut(t);
            case EaseType::BackIn: return EaseFunctions::backIn(t);
            case EaseType::BackOut: return EaseFunctions::backOut(t);
            case EaseType::BackInOut: return EaseFunctions::backInOut(t);
            case EaseType::ElasticIn: return EaseFunctions::elasticIn(t);
            case EaseType::ElasticOut: return EaseFunctions::elasticOut(t);
            case EaseType::ElasticInOut: return EaseFunctions::elasticInOut(t);
            case EaseType::BounceIn: return EaseFunctions::bounceIn(t);
            case EaseType::BounceOut: return EaseFunctions::bounceOut(t);
            case EaseType::BounceInOut: return EaseFunctions::bounceInOut(t);
            default: return t;
        }
    }
    
    template<typename T>
    T easeLerp(const T& a, const T& b, float t, EaseType type) {
        return lerp(a, b, ease(t, type));
    }
    
    template<typename T>
    T cubicInterpolate(const T& p0, const T& p1, const T& p2, const T& p3, float t) {
        T t2 = t * t;
        T t3 = t2 * t;
        return p1 + 0.5f * t * (p2 - p0 + t * (2.0f * p0 - 5.0f * p1 + 4.0f * p2 - p3 + t * (3.0f * (p1 - p2) + p3 - p0)));
    }
    
    template<typename T>
    T bilinearInterpolate(const T& v00, const T& v10, const T& v01, const T& v11,
                          float tx, float ty) {
        return lerp(lerp(v00, v10, tx), lerp(v01, v11, tx), ty);
    }
    
    template<typename T>
    T trilinearInterpolate(const T& v000, const T& v100, const T& v010, const T& v110,
                           const T& v001, const T& v101, const T& v011, const T& v111,
                           float tx, float ty, float tz) {
        T v0 = bilinearInterpolate(v000, v100, v010, v110, tx, ty);
        T v1 = bilinearInterpolate(v001, v101, v011, v111, tx, ty);
        return lerp(v0, v1, tz);
    }
    
    template<typename T>
    T bezier(const T& p0, const T& p1, const T& p2, float t) {
        return lerp(lerp(p0, p1, t), lerp(p1, p2, t), t);
    }
    
    template<typename T>
    T bezier(const T& p0, const T& p1, const T& p2, const T& p3, float t) {
        return lerp(lerp(lerp(p0, p1, t), lerp(p1, p2, t), t), lerp(lerp(p1, p2, t), lerp(p2, p3, t), t), t);
    }
    
    template<typename T>
    T pathInterpolate(const std::vector<T>& points, float t) {
        if (points.empty()) return T();
        if (points.size() == 1) return points[0];
        
        float scaledT = t * (points.size() - 1);
        size_t index = static_cast<size_t>(scaledT);
        float localT = scaledT - index;
        
        if (index >= points.size() - 1) return points.back();
        return lerp(points[index], points[index + 1], localT);
    }
}