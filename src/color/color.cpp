#include "../../include/color/color.hpp"
#include <algorithm>

// Constructor

Color::Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}

// Static methods

Color Color::fromRGB(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    return Color(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
}

Color Color::fromHex(uint32_t hex) {
    float red = ((hex >> 16) & 0xFF) / 255.0f;
    float green = ((hex >> 8) & 0xFF) / 255.0f;
    float blue = (hex & 0xFF) / 255.0f;
    float alpha = ((hex >> 24) & 0xFF) / 255.0f;
    return Color(red, green, blue, alpha);
}

Color Color::fromHSV(float h, float s, float v, float a) {
    h = std::fmod(h, 360.0f);
    if (h < 0) h += 360.0f;
    s = std::clamp(s, 0.0f, 1.0f);
    v = std::clamp(v, 0.0f, 1.0f);

    float c = v * s;
    float x = c * (1 - std::abs(static_cast<float>(std::fmod(h / 60.0f, 2)) - 1));
    float m = v - c;

    float red, green, blue;
    if (h < 60) {
        red = c; green = x; blue = 0;
    } else if (h < 120) {
        red = x; green = c; blue = 0;
    } else if (h < 180) {
        red = 0; green = c; blue = x;
    } else if (h < 240) {
        red = 0; green = x; blue = c;
    } else if (h < 300) {
        red = x; green = 0; blue = c;
    } else {
        red = c; green = 0; blue = x;
    }

    return Color(red + m, green + m, blue + m, a);
}

Color Color::fromHSL(float h, float s, float l, float a) {
    h = std::fmod(h, 360.0f);
    if (h < 0) h += 360.0f;
    s = std::clamp(s, 0.0f, 1.0f);
    l = std::clamp(l, 0.0f, 1.0f);

    float c = (1 - std::abs(2 * l - 1)) * s;
    float x = c * (1 - std::abs(static_cast<float>(std::fmod(h / 60.0f, 2)) - 1));
    float m = l - c / 2;

    float red, green, blue;
    if (h < 60) {
        red = c; green = x; blue = 0;
    } else if (h < 120) {
        red = x; green = c; blue = 0;
    } else if (h < 180) {
        red = 0; green = c; blue = x;
    } else if (h < 240) {
        red = 0; green = x; blue = c;
    } else if (h < 300) {
        red = x; green = 0; blue = c;
    } else {
        red = c; green = 0; blue = x;
    }

    return Color(red + m, green + m, blue + m, a);
}

// Conversion methods

Vector3f Color::toVector3() const {
    return Vector3f(r, g, b);
}

Vector4f Color::toVector4() const {
    return Vector4f(r, g, b, a);
}

uint32_t Color::toRGBA() const {
    return ((uint32_t)(r * 255) << 24) | ((uint32_t)(g * 255) << 16) | ((uint32_t)(b * 255) << 8) | (uint32_t)(a * 255);
}

uint32_t Color::toARGB() const {
    return ((uint32_t)(a * 255) << 24) | ((uint32_t)(r * 255) << 16) | ((uint32_t)(g * 255) << 8) | (uint32_t)(b * 255);
}

uint32_t Color::toABGR() const {
    return ((uint32_t)(a * 255) << 24) | ((uint32_t)(b * 255) << 16) | ((uint32_t)(g * 255) << 8) | (uint32_t)(r * 255);
}

void Color::toHSV(float& h, float& s, float& v) const {
    float max = std::max(std::max(r, g), b);
    float min = std::min(std::min(r, g), b);
    float delta = max - min;

    v = max;
    if (max != 0) {
        s = delta / max;
    } else {
        s = 0;
        h = 0;
        return;
    }

    if (delta == 0) {
        h = 0;
    } else {
        if (max == r) {
            h = 60 * static_cast<float>(std::fmod((g - b) / delta, 6));
        } else if (max == g) {
            h = 60 * (((b - r) / delta) + 2);
        } else {
            h = 60 * (((r - g) / delta) + 4);
        }
        if (h < 0) h += 360;
    }
}

void Color::toHSL(float& h, float& s, float& l) const {
    float max = std::max(std::max(r, g), b);
    float min = std::min(std::min(r, g), b);
    float delta = max - min;

    l = (max + min) / 2;
    if (delta == 0) {
        h = 0;
        s = 0;
    } else {
        s = delta / (1 - std::abs(2 * l - 1));
        if (max == r) {
            h = 60 * static_cast<float>(std::fmod((g - b) / delta, 6));
        } else if (max == g) {
            h = 60 * (((b - r) / delta) + 2);
        } else {
            h = 60 * (((r - g) / delta) + 4);
        }
        if (h < 0) h += 360;
    }
}

Color Color::toHSV() const {
    float h, s, v;
    toHSV(h, s, v);
    return Color(h, s, v, a);
}

Color Color::toHSL() const {
    float h, s, l;
    toHSL(h, s, l);
    return Color(h, s, l, a);
}

Color Color::fromHSV(const Color& hsv) const {
    return fromHSV(hsv.r, hsv.g, hsv.b, hsv.a);
}

Color Color::fromHSL(const Color& hsl) const {
    return fromHSL(hsl.r, hsl.g, hsl.b, hsl.a);
}

// Operator overloads

Color Color::operator+(const Color& other) const {
    return Color(r + other.r, g + other.g, b + other.b, a + other.a);
}

Color Color::operator-(const Color& other) const {
    return Color(r - other.r, g - other.g, b - other.b, a - other.a);
}

Color Color::operator*(float scalar) const {
    return Color(r * scalar, g * scalar, b * scalar, a * scalar);
}

Color Color::operator*(const Color& other) const {
    return Color(r * other.r, g * other.g, b * other.b, a * other.a);
}

Color& Color::operator+=(const Color& other) {
    r += other.r;
    g += other.g;
    b += other.b;
    a += other.a;
    return *this;
}

Color& Color::operator*=(float scalar) {
    r *= scalar;
    g *= scalar;
    b *= scalar;
    a *= scalar;
    return *this;
}

// Interpolation

Color Color::lerp(const Color& other, float t) const {
    return Color(
        r + (other.r - r) * t,
        g + (other.g - g) * t,
        b + (other.b - b) * t,
        a + (other.a - a) * t
    );
}

Color Color::lerp(const Color& a, const Color& b, float t) {
    return Color(
        a.r + (b.r - a.r) * t,
        a.g + (b.g - a.g) * t,
        a.b + (b.b - a.b) * t,
        a.a + (b.a - a.a) * t
    );
}

// Color manipulation

Color Color::gammaCorrected(float gamma) const {
    return Color(
        std::pow(r, gamma),
        std::pow(g, gamma),
        std::pow(b, gamma),
        a
    );
}

Color Color::inverseGammaCorrected(float gamma) const {
    return Color(
        std::pow(r, 1.0f / gamma),
        std::pow(g, 1.0f / gamma),
        std::pow(b, 1.0f / gamma),
        a
    );
}

float Color::luminance() const {
    return 0.2126f * r + 0.7152f * g + 0.0722f * b;
}

Color Color::brightened(float amount) const {
    return Color(
        std::clamp(r + amount, 0.0f, 1.0f),
        std::clamp(g + amount, 0.0f, 1.0f),
        std::clamp(b + amount, 0.0f, 1.0f),
        a
    );
}

Color Color::darkened(float amount) const {
    return Color(
        std::clamp(r - amount, 0.0f, 1.0f),
        std::clamp(g - amount, 0.0f, 1.0f),
        std::clamp(b - amount, 0.0f, 1.0f),
        a
    );
}

Color Color::saturated(float amount) const {
    float h, s, v;
    toHSV(h, s, v);
    s = std::clamp(s + amount, 0.0f, 1.0f);
    return fromHSV(h, s, v, a);
}

Color Color::desaturated(float amount) const {
    float h, s, v;
    toHSV(h, s, v);
    s = std::clamp(s - amount, 0.0f, 1.0f);
    return fromHSV(h, s, v, a);
}

Color Color::inverted() const {
    return Color(1.0f - r, 1.0f - g, 1.0f - b, a);
}

Color Color::withAlpha(float alpha) const {
    return Color(r, g, b, alpha);
}

Color Color::premultipliedAlpha() const {
    return Color(r * a, g * a, b * a, a);
}

// Static color constants

Color Color::white() {
    return Color(1.0f, 1.0f, 1.0f, 1.0f);
}

Color Color::black() {
    return Color(0.0f, 0.0f, 0.0f, 1.0f);
}

Color Color::red() {
    return Color(1.0f, 0.0f, 0.0f, 1.0f);
}

Color Color::green() {
    return Color(0.0f, 1.0f, 0.0f, 1.0f);
}

Color Color::blue() {
    return Color(0.0f, 0.0f, 1.0f, 1.0f);
}

Color Color::yellow() {
    return Color(1.0f, 1.0f, 0.0f, 1.0f);
}

Color Color::magenta() {
    return Color(1.0f, 0.0f, 1.0f, 1.0f);
}

Color Color::cyan() {
    return Color(0.0f, 1.0f, 1.0f, 1.0f);
}

Color Color::transparent() {
    return Color(0.0f, 0.0f, 0.0f, 0.0f);
}

// Getters and setters

float Color::getR() const {
    return r;
}

float Color::getG() const {
    return g;
}

float Color::getB() const {
    return b;
}

float Color::getA() const {
    return a;
}

void Color::setR(float value) {
    r = value;
}

void Color::setG(float value) {
    g = value;
}

void Color::setB(float value) {
    b = value;
}

void Color::setA(float value) {
    a = value;
}

// Equality check

bool Color::equals(const Color& other, float epsilon) const {
    return std::abs(r - other.r) < epsilon &&
           std::abs(g - other.g) < epsilon &&
           std::abs(b - other.b) < epsilon &&
           std::abs(a - other.a) < epsilon;
}

Color Color::clone() const {
    return Color(r, g, b, a);
}
