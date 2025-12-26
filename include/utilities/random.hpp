#pragma once
#include <cstdint>
#include <random>
#include <vector>
#include <algorithm>
#include "../vectors/vector2.hpp"
#include "../vectors/vector3.hpp"
#include "../vectors/vector4.hpp"
#include "../color/color.hpp"
#include <cmath>

class Random {
private:
    static thread_local std::mt19937 generator;
    
public:
    // Initialization
    static void seed(uint32_t seed);
    static void seed();
     
    // Basic generators
    static int32_t range(int32_t min, int32_t max);
    static uint32_t range(uint32_t min, uint32_t max);
    static float range(float min, float max);
    static double range(double min, double max);
     
    // Special distributions
    static float normal(float mean = 0.0f, float stddev = 1.0f);
    static float exponential(float lambda = 1.0f);
    static float gamma(float alpha, float beta = 1.0f);
     
    // Vectors
    static Vector2f vector2(float min = 0.0f, float max = 1.0f);
    static Vector3f vector3(float min = 0.0f, float max = 1.0f);
    static Vector4f vector4(float min = 0.0f, float max = 1.0f);
     
    // Random point in circle/sphere
    static Vector2f pointInCircle(float radius = 1.0f);
    static Vector3f pointInSphere(float radius = 1.0f);
    static Vector2f pointOnCircle(float radius = 1.0f);
    static Vector3f pointOnSphere(float radius = 1.0f);
     
    // Colors
    static Color color(bool randomAlpha = false);
    static Color colorHSV(float minH = 0.0f, float maxH = 360.0f,
                          float minS = 0.5f, float maxS = 1.0f,
                          float minV = 0.5f, float maxV = 1.0f);
     
    // Random choice
    template<typename T>
    static const T& choice(const std::vector<T>& items);
     
    template<typename T>
    static T& choice(std::vector<T>& items);
     
    // Noise
    static float perlinNoise(float x, float y);
    static float perlinNoise(float x, float y, float z);
    static float simplexNoise(float x, float y);
     
    // Probabilities
    static bool chance(float probability);
     
    // Shuffling
    template<typename T>
    static void shuffle(std::vector<T>& items);
     
    // Gradient noise
    static float gradientNoise(int x, int y, int seed = 0);
    static float gradientNoise(float x, float y, int seed = 0);
     
    // Additional methods
    template<typename Container>
    static typename Container::value_type choice(const Container& container);
    
    static bool bernoulli(float p = 0.5f);
    static int32_t binomial(int32_t n, float p = 0.5f);
    
private:
    static float lerp(float a, float b, float t);
};
