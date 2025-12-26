#pragma once
#include "../vectors/vector3.hpp"
#include "../vectors/vector4.hpp"
#include <cstdint>
#include <cmath>
#include <algorithm>

class Color {
private:
    float r, g, b, a;
    
public:
    Color(float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 1.0f);
    
    static Color fromRGB(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);
    static Color fromHex(uint32_t hex);
    static Color fromHSV(float h, float s, float v, float a = 1.0f);
    static Color fromHSL(float h, float s, float l, float a = 1.0f);
    
    Vector3f toVector3() const;
    Vector4f toVector4() const;
    uint32_t toRGBA() const;
    uint32_t toARGB() const;
    uint32_t toABGR() const;
    
    void toHSV(float& h, float& s, float& v) const;
    void toHSL(float& h, float& s, float& l) const;
    Color toHSV() const;
    Color toHSL() const;
    Color fromHSV(const Color& hsv) const;
    Color fromHSL(const Color& hsl) const;
    
    Color operator+(const Color& other) const;
    Color operator-(const Color& other) const;
    Color operator*(float scalar) const;
    Color operator*(const Color& other) const;
    Color& operator+=(const Color& other);
    Color& operator*=(float scalar);
    
    Color lerp(const Color& other, float t) const;
    static Color lerp(const Color& a, const Color& b, float t);
    
    Color gammaCorrected(float gamma = 2.2f) const;
    Color inverseGammaCorrected(float gamma = 2.2f) const;
    float luminance() const;
    Color brightened(float amount) const;
    Color darkened(float amount) const;
    Color saturated(float amount) const;
    Color desaturated(float amount) const;
    Color inverted() const;
    Color withAlpha(float alpha) const;
    Color premultipliedAlpha() const;
    
    static Color white();
    static Color black();
    static Color red();
    static Color green();
    static Color blue();
    static Color yellow();
    static Color magenta();
    static Color cyan();
    static Color transparent();
    
    float getR() const;
    float getG() const;
    float getB() const;
    float getA() const;
    
    void setR(float value);
    void setG(float value);
    void setB(float value);
    void setA(float value);
    
    bool equals(const Color& other, float epsilon = 0.001f) const;
    Color clone() const;
};
