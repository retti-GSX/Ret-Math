#include "../../include/utilities/random.hpp"
#include <stdexcept>

thread_local std::mt19937 Random::generator;

// Initialization

void Random::seed(uint32_t seed) {
    generator.seed(seed);
}

void Random::seed() {
    std::random_device rd;
    generator.seed(rd());
}

// Basic generators

int32_t Random::range(int32_t min, int32_t max) {
    std::uniform_int_distribution<int32_t> dist(min, max);
    return dist(generator);
}

uint32_t Random::range(uint32_t min, uint32_t max) {
    std::uniform_int_distribution<uint32_t> dist(min, max);
    return dist(generator);
}

float Random::range(float min, float max) {
    std::uniform_real_distribution<float> dist(min, max);
    return dist(generator);
}

double Random::range(double min, double max) {
    std::uniform_real_distribution<double> dist(min, max);
    return dist(generator);
}

// Special distributions

float Random::normal(float mean, float stddev) {
    std::normal_distribution<float> dist(mean, stddev);
    return dist(generator);
}

float Random::exponential(float lambda) {
    std::exponential_distribution<float> dist(lambda);
    return dist(generator);
}

float Random::gamma(float alpha, float beta) {
    std::gamma_distribution<float> dist(alpha, beta);
    return dist(generator);
}

// Vectors

Vector2f Random::vector2(float min, float max) {
    return Vector2f(range(min, max), range(min, max));
}

Vector3f Random::vector3(float min, float max) {
    return Vector3f(range(min, max), range(min, max), range(min, max));
}

Vector4f Random::vector4(float min, float max) {
    return Vector4f(range(min, max), range(min, max), range(min, max), range(min, max));
}

// Random point in circle/sphere

Vector2f Random::pointInCircle(float radius) {
    float angle = range(0.0f, 2 * 3.14159265358979323846f);
    float distance = std::sqrt(range(0.0f, 1.0f)) * radius;
    return Vector2f(distance * std::cos(angle), distance * std::sin(angle));
}

Vector3f Random::pointInSphere(float radius) {
    float theta = range(0.0f, 2 * 3.14159265358979323846f);
    float phi = std::acos(range(-1.0f, 1.0f));
    float distance = std::pow(range(0.0f, 1.0f), 1.0f / 3.0f) * radius;
    return Vector3f(
        distance * std::sin(phi) * std::cos(theta),
        distance * std::sin(phi) * std::sin(theta),
        distance * std::cos(phi)
    );
}

Vector2f Random::pointOnCircle(float radius) {
    float angle = range(0.0f, 2 * 3.14159265358979323846f);
    return Vector2f(radius * std::cos(angle), radius * std::sin(angle));
}

Vector3f Random::pointOnSphere(float radius) {
    float theta = range(0.0f, 2 * 3.14159265358979323846f);
    float phi = std::acos(range(-1.0f, 1.0f));
    return Vector3f(
        radius * std::sin(phi) * std::cos(theta),
        radius * std::sin(phi) * std::sin(theta),
        radius * std::cos(phi)
    );
}

// Colors

Color Random::color(bool randomAlpha) {
    return Color(range(0.0f, 1.0f), range(0.0f, 1.0f), range(0.0f, 1.0f), randomAlpha ? range(0.0f, 1.0f) : 1.0f);
}

Color Random::colorHSV(float minH, float maxH,
                      float minS, float maxS,
                      float minV, float maxV) {
    return Color::fromHSV(range(minH, maxH), range(minS, maxS), range(minV, maxV));
}

// Random choice

template<typename T>
const T& Random::choice(const std::vector<T>& items) {
    if (items.empty()) {
        throw std::runtime_error("Cannot choose from empty vector");
    }
    std::uniform_int_distribution<size_t> dist(0, items.size() - 1);
    return items[dist(generator)];
}

template<typename T>
T& Random::choice(std::vector<T>& items) {
    if (items.empty()) {
        throw std::runtime_error("Cannot choose from empty vector");
    }
    std::uniform_int_distribution<size_t> dist(0, items.size() - 1);
    return items[dist(generator)];
}

// Noise

float Random::perlinNoise(float x, float y) {
    // Simplified Perlin noise implementation
    int x0 = static_cast<int>(x);
    int y0 = static_cast<int>(y);
    int x1 = x0 + 1;
    int y1 = y0 + 1;
    
    float sx = x - x0;
    float sy = y - y0;
    
    float n0 = gradientNoise(x0, y0);
    float n1 = gradientNoise(x1, y0);
    float ix0 = lerp(n0, n1, sx);
    
    n0 = gradientNoise(x0, y1);
    n1 = gradientNoise(x1, y1);
    float ix1 = lerp(n0, n1, sx);
    
    return lerp(ix0, ix1, sy);
}

float Random::perlinNoise(float x, float y, float z) {
    // Simplified Perlin noise implementation
    int x0 = static_cast<int>(x);
    int y0 = static_cast<int>(y);
    int z0 = static_cast<int>(z);
    int x1 = x0 + 1;
    int y1 = y0 + 1;
    int z1 = z0 + 1;
    
    float sx = x - x0;
    float sy = y - y0;
    float sz = z - z0;
    
    float n0 = gradientNoise(x0, y0, z0);
    float n1 = gradientNoise(x1, y0, z0);
    float ix0 = lerp(n0, n1, sx);
    
    n0 = gradientNoise(x0, y1, z0);
    n1 = gradientNoise(x1, y1, z0);
    float ix1 = lerp(n0, n1, sx);
    
    float iy0 = lerp(ix0, ix1, sy);
    
    n0 = gradientNoise(x0, y0, z1);
    n1 = gradientNoise(x1, y0, z1);
    ix0 = lerp(n0, n1, sx);
    
    n0 = gradientNoise(x0, y1, z1);
    n1 = gradientNoise(x1, y1, z1);
    ix1 = lerp(n0, n1, sx);
    
    float iy1 = lerp(ix0, ix1, sy);
    
    return lerp(iy0, iy1, sz);
}

float Random::simplexNoise(float x, float y) {
    // Simplified simplex noise implementation
    return perlinNoise(x, y);
}

// Probabilities

bool Random::chance(float probability) {
    return range(0.0f, 1.0f) < probability;
}

// Shuffling

template<typename T>
void Random::shuffle(std::vector<T>& items) {
    std::shuffle(items.begin(), items.end(), generator);
}

// Gradient noise

float Random::gradientNoise(int x, int y, int seed) {
    uint32_t hash = (x * 1664525 + y * 1013904223 + seed) & 0xFFFFFFFF;
    hash = (hash ^ (hash >> 13)) * 1274126177;
    return static_cast<float>(hash) / static_cast<float>(0xFFFFFFFF);
}

float Random::gradientNoise(float x, float y, int seed) {
    return gradientNoise(static_cast<int>(x), static_cast<int>(y), seed);
}

// Additional methods

template<typename Container>
typename Container::value_type Random::choice(const Container& container) {
    if (container.empty()) {
        throw std::runtime_error("Cannot choose from empty container");
    }
    std::uniform_int_distribution<size_t> dist(0, container.size() - 1);
    return container[dist(generator)];
}

bool Random::bernoulli(float p) {
    return chance(p);
}

int32_t Random::binomial(int32_t n, float p) {
    std::binomial_distribution<int32_t> dist(n, p);
    return dist(generator);
}

// Private methods

float Random::lerp(float a, float b, float t) {
    return a + (b - a) * t;
}
