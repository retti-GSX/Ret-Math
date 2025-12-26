/// ../docs/.gif <- result this script
/**
 * @file main.cpp
 * @brief Gravity Simulation using RetMath Library
 * @version 2.0
 */

#include "RetMath.hpp"   /* <- import RetMath*/
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <iomanip>

/**
 * @class CelestialBody
 * @brief Celestial body with physics properties
 */
class CelestialBody {
public:
    Vec2 position;      ///< Position in pixels
    Vec2 velocity;      ///< Velocity in px/s
    Vec2 acceleration;  ///< Acceleration in px/s²
    float mass;         ///< Mass (affects gravity)
    char symbol;        ///< Visual character
    
    /**
     * @param pos Initial position
     * @param vel Initial velocity
     * @param m Mass (must be > 0)
     * @param sym Display symbol
     */
    CelestialBody(Vec2 pos, Vec2 vel, float m, char sym)
        : position(pos), velocity(vel), mass(m), symbol(sym) {
        if (m <= 0.0f) throw std::invalid_argument("Mass must be positive");
    }
    
    /** 
     * @brief Update physics (Verlet integration)
     * @param dt Time step in seconds
     */
    void update(float dt) {
        velocity = velocity + acceleration * dt;
        position = position + velocity * dt;
        acceleration = Vec2(0, 0);
    }
    
    /**
     * @brief Apply force: a = F/m
     */
    void applyForce(Vec2 force) {
        acceleration = acceleration + force / mass;
    }
};

/**
 * @class GravitySimulation
 * @brief N-body gravitational simulation
 */
class GravitySimulation {
private:
    std::vector<CelestialBody> bodies;
    const float G = 100.0f;           ///< Gravitational constant (tuned for ASCII)
    const float width = 80;
    const float height = 40;
    
    int targetFPS = 60;
    float targetFrameTime;
    std::chrono::steady_clock::time_point lastFrameTime;
    float currentFPS = 0.0f;
    int frameCount = 0;
    std::chrono::steady_clock::time_point fpsUpdateTime;
    
public:
    GravitySimulation() : targetFrameTime(1.0f / targetFPS), 
                         lastFrameTime(std::chrono::steady_clock::now()),
                         fpsUpdateTime(std::chrono::steady_clock::now()) {}
    
    void addBody(const CelestialBody& body) {
        bodies.push_back(body);
    }
    
    /**
     * @brief Update simulation
     * @param dt Time step
     * 
     * Calculates gravitational forces (F = G*m1*m2/r²) between all pairs,
     * updates positions, handles boundary collisions.
     * @complexity O(n²)
     */
    void update(float dt) {
        // Calculate forces between all pairs
        for (size_t i = 0; i < bodies.size(); ++i) {
            for (size_t j = i + 1; j < bodies.size(); ++j) {
                Vec2 delta = bodies[j].position - bodies[i].position;
                float distanceSq = delta.lengthSquared();
                if (distanceSq < 1.0f) distanceSq = 1.0f; // Prevent division by zero
                
                float forceMagnitude = G * bodies[i].mass * bodies[j].mass / distanceSq;
                Vec2 force = delta.normalized() * forceMagnitude;
                
                bodies[i].applyForce(force);
                bodies[j].applyForce(force * -1.0f);
            }
        }
        
        // Update positions and handle boundaries
        for (auto& body : bodies) {
            body.update(dt);
            
            if (body.position.x < 0 || body.position.x >= width) {
                body.velocity.x *= -0.9f;
                body.position.x = Math::clamp(body.position.x, 0.0f, width - 1);
            }
            
            if (body.position.y < 0 || body.position.y >= height) {
                body.velocity.y *= -0.9f;
                body.position.y = Math::clamp(body.position.y, 0.0f, height - 1);
            }
        }
    }
    
    void calculateFPS() {
        frameCount++;
        auto currentTime = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
            currentTime - fpsUpdateTime).count();
        
        if (elapsed >= 1000) {
            currentFPS = (frameCount * 1000.0f) / elapsed;
            frameCount = 0;
            fpsUpdateTime = currentTime;
        }
    }
    
    float getCurrentFPS() const { return currentFPS; }
    
    void setTargetFPS(int fps) { 
        if (fps <= 0 || fps > 120) {
            throw std::invalid_argument("FPS must be 1-120");
        }
        targetFPS = fps; 
        targetFrameTime = 1.0f / fps; 
    }
    
    /**
     * @brief Render ASCII visualization
     */
    void render() {
        std::cout << "\033[H\033[2J"; // Clear screen
        
        std::vector<std::string> canvas(height, std::string(width, ' '));
        
        // Draw axes
        int midY = height / 2;
        int midX = width / 2;
        for (int x = 0; x < width; ++x) canvas[midY][x] = '-';
        for (int y = 0; y < height; ++y) canvas[y][midX] = '|';
        canvas[midY][midX] = '+';
        
        // Draw bodies
        for (const auto& body : bodies) {
            int x = Math::floorToInt(body.position.x);
            int y = Math::floorToInt(body.position.y);
            if (x >= 0 && x < width && y >= 0 && y < height) {
                canvas[y][x] = body.symbol;
            }
        }
        
        for (const auto& row : canvas) std::cout << row << "\n";
        std::cout << "\nBodies: " << bodies.size() << " | FPS: " 
                  << std::fixed << std::setprecision(1) << currentFPS << "\n";
    }
    
    /**
     * @brief Run simulation
     * @param frames Number of frames to simulate
     * @param dt Default time step (0.016 ≈ 60fps)
     */
    void run(int frames, float dt = 0.016f) {
        if (frames <= 0) throw std::invalid_argument("Frames must be > 0");
        
        std::cout << "Starting simulation at " << targetFPS << " FPS...\n";
        std::cout << "Press Ctrl+C to stop\n\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
        
        for (int i = 0; i < frames; ++i) {
            auto frameStart = std::chrono::steady_clock::now();
            
            auto timeSinceLastFrame = std::chrono::duration_cast<std::chrono::microseconds>(
                frameStart - lastFrameTime);
            float actualDt = timeSinceLastFrame.count() / 1000000.0f;
            actualDt = std::min(actualDt, 0.033f); // Clamp for stability
            
            update(actualDt);
            render();
            calculateFPS();
            
            // Frame rate limiting
            auto frameEnd = std::chrono::steady_clock::now();
            auto frameTime = std::chrono::duration_cast<std::chrono::microseconds>(
                frameEnd - frameStart);
            auto sleepDuration = std::chrono::microseconds(
                (long long)(targetFrameTime * 1000000)) - frameTime;
            
            if (sleepDuration.count() > 0) {
                std::this_thread::sleep_for(sleepDuration);
            }
            
            lastFrameTime = frameStart;
        }
        
        std::cout << "\nSimulation completed.\n";
        std::cout << "Final FPS: " << currentFPS << "\n";
    }
};

/**
 * @brief Main entry point
 * 
 * Creates 4-body gravitational system with ASCII visualization.
 * Uses RetMath for vector operations, clamping, and coordinate conversion.
 */
int main() {
    try {
        GravitySimulation sim;
        sim.setTargetFPS(60);
        
        // Add celestial bodies
        sim.addBody(CelestialBody(Vec2(20, 20), Vec2(0, 5), 10.0f, 'S'));   // Sun
        sim.addBody(CelestialBody(Vec2(60, 20), Vec2(0, -5), 8.0f, 'M'));   // Planet
        sim.addBody(CelestialBody(Vec2(40, 10), Vec2(5, 0), 5.0f, 'E'));    // Moon
        sim.addBody(CelestialBody(Vec2(40, 30), Vec2(-5, 0), 3.0f, 'm'));   // Satellite
        
        sim.run(1000);
        
        std::cout << "Simulation completed successfully.\n";
        return 0;
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
}

/**
 * @page retmath_usage RetMath Usage Summary
 * 
 * @section vectors Vec2 Operations
 * - Construction: Vec2(x, y)
 * - Arithmetic: +, -, *, / (vector and scalar)
 * - Methods: lengthSquared(), normalized()
 * 
 * @section math_utils Math Utilities
 * - Math::clamp(value, min, max) - boundary constraints
 * - Math::floorToInt(float) - float to int conversion
 * 
 * @section performance Performance Notes
 * - lengthSquared() avoids expensive sqrt()
 * - O(n²) gravitational calculation
 * - Frame limiting prevents CPU overuse
 * - Delta time clamping ensures stability
 */
