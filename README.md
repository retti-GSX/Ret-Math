# RetMath - Mathematics Library for Games and Graphics (MIT)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)
[![Documentation](https://img.shields.io/badge/documentation-📘-informational)](docs/)

RetMath is a comprehensive C++ mathematics library designed for game development, computer graphics, and real-time applications. It provides a wide range of mathematical structures and functions for working with vectors, matrices, quaternions, geometry, transformations, colors, and various utility functions.

<div align="center">
  <img src="2dgravity.gif.gif" alt="RetMath Library Demo" width="800"/>
  <br>
  <em>Demonstration of vector operations, matrix transformations, and collision detection</em>
  
  <div style="margin: 20px 0;">
    <details>
    <summary style="display: inline-flex; align-items: center; gap: 10px; padding: 12px 24px; background: #2d3748; color: white; border-radius: 6px; cursor: pointer; border: 2px solid #4a5568;">
      <svg width="16" height="16" fill="currentColor" viewBox="0 0 16 16">
        <path d="M8 15A7 7 0 1 1 8 1a7 7 0 0 1 0 14zm0 1A8 8 0 1 0 8 0a8 8 0 0 0 0 16z"/>
        <path d="M8 4a.5.5 0 0 1 .5.5v3h3a.5.5 0 0 1 0 1h-3v3a.5.5 0 0 1-1 0v-3h-3a.5.5 0 0 1 0-1h3v-3A.5.5 0 0 1 8 4z"/>
      </svg>
      <b>Reveal demo code</b>
    </summary>
    
    ```cpp
#include "RetMath.hpp"
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <iomanip>

class CelestialBody {
public:
    Vec2 position;
    Vec2 velocity;
    Vec2 acceleration;
    float mass;
    char symbol;
    
    CelestialBody(Vec2 pos, Vec2 vel, float m, char sym)
        : position(pos), velocity(vel), mass(m), symbol(sym) {}
    
    void update(float dt) {
        velocity = velocity + acceleration * dt;
        position = position + velocity * dt;
        acceleration = Vec2(0, 0); // reset acceleration
    }
    
    void applyForce(Vec2 force) {
        acceleration = acceleration + force / mass;
    }
};

class GravitySimulation {
private:
    std::vector<CelestialBody> bodies;
    const float G = 100.0f; // гравітаційна стала для ASCII масштабу
    const float width = 80;
    const float height = 40;
    
    // Performance optimization
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
    
public:
    void addBody(const CelestialBody& body) {
        bodies.push_back(body);
    }
    
    void update(float dt) {
        // Calculate gravitational forces
        for (size_t i = 0; i < bodies.size(); ++i) {
            for (size_t j = i + 1; j < bodies.size(); ++j) {
                Vec2 delta = bodies[j].position - bodies[i].position;
                float distanceSq = delta.lengthSquared();
                if (distanceSq < 1.0f) distanceSq = 1.0f; // prevent division by zero
                
                float forceMagnitude = G * bodies[i].mass * bodies[j].mass / distanceSq;
                Vec2 force = delta.normalized() * forceMagnitude;
                
                bodies[i].applyForce(force);
                bodies[j].applyForce(force * -1.0f);
            }
        }
        
    // Update positions
        for (auto& body : bodies) {
            body.update(dt);
            
    // Boundary reflection
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
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - fpsUpdateTime).count();
        
        if (elapsed >= 1000) { // Update FPS every second
            currentFPS = (frameCount * 1000.0f) / elapsed;
            frameCount = 0;
            fpsUpdateTime = currentTime;
        }
    }
    
    float getCurrentFPS() const { return currentFPS; }
    void setTargetFPS(int fps) { 
        targetFPS = fps; 
        targetFrameTime = 1.0f / fps; 
    }
    
    void render() {
        // Clear screen
        std::cout << "\033[H\033[2J";
        
        // Create ASCII canvas
        std::vector<std::string> canvas(height, std::string(width, ' '));
        
        // Add coordinate axes (cross in the middle)
        int midY = height / 2;
        int midX = width / 2;
        
        for (int x = 0; x < width; ++x) {
            canvas[midY][x] = '-';
        }
        
        for (int y = 0; y < height; ++y) {
            canvas[y][midX] = '|';
        }
        
        // Center cross
        canvas[midY][midX] = '+';
        
        // Add bodies
        for (const auto& body : bodies) {
            int x = Math::floorToInt(body.position.x);
            int y = Math::floorToInt(body.position.y);
            
            if (x >= 0 && x < width && y >= 0 && y < height) {
                canvas[y][x] = body.symbol;
            }
        }
        
        // Output canvas
        for (const auto& row : canvas) {
            std::cout << row << "\n";
        }
        
        // Simple info display
        std::cout << "\nBodies: " << bodies.size() << " | FPS: " 
                  << std::fixed << std::setprecision(1) << currentFPS << "\n";
    }
    
    void run(int frames, float dt = 0.016f) {
        std::cout << "Starting simulation at " << targetFPS << " FPS...\n";
        std::cout << "Press Ctrl+C to stop\n\n";
        
        std::this_thread::sleep_for(std::chrono::seconds(1));
        
        for (int i = 0; i < frames; ++i) {
            auto frameStart = std::chrono::steady_clock::now();
            
            // Calculate time since last frame
            auto timeSinceLastFrame = std::chrono::duration_cast<std::chrono::microseconds>(
                frameStart - lastFrameTime);
            float actualDt = timeSinceLastFrame.count() / 1000000.0f;
            
            // Clamp dt for stability
            actualDt = std::min(actualDt, 0.033f);
            
            update(actualDt);
            render();
            calculateFPS();
            
            // Frame rate control
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
    }
    

};

int main() {
    GravitySimulation sim;
    
    // Set FPS
    sim.setTargetFPS(60);
    
    // Add bodies
    sim.addBody(CelestialBody(Vec2(20, 20), Vec2(0, 5), 10.0f, 'S'));
    sim.addBody(CelestialBody(Vec2(60, 20), Vec2(0, -5), 8.0f, 'M'));
    sim.addBody(CelestialBody(Vec2(40, 10), Vec2(5, 0), 5.0f, 'E'));
    sim.addBody(CelestialBody(Vec2(40, 30), Vec2(-5, 0), 3.0f, 'm'));
    
    // Run simulation
    sim.run(1000);
    
    return 0;
}
    ```
  </div>
</div>

## Features

### Vectors
- **Vector2**: 2D vectors for points and directions
- **Vector3**: 3D vectors for points, directions, and colors
- **Vector4**: 4D vectors for homogeneous coordinates
- Common operations: normalization, dot/cross products, interpolation

### Matrices
- **Matrix2x2**: 2×2 matrices for 2D linear transformations
- **Matrix3x3**: 3×3 matrices for 3D linear transformations
- **Matrix4x4**: 4×4 matrices for 3D affine transformations
- Specialized matrices: translation, rotation, scaling, perspective, orthographic, view (lookAt)

### Quaternions
- Efficient 3D rotation representation
- Conversion to/from matrices and Euler angles
- Spherical linear interpolation (SLERP)
- Normalization and inversion operations

### Geometry
- **Plane**: 3D planes with distance calculations
- **Ray**: Ray casting and intersection testing
- **Rect**: 2D rectangles with containment checks
- **Circle**: 2D circles with intersection testing
- **AABB**: Axis-Aligned Bounding Boxes
- **OBB**: Oriented Bounding Boxes
- **Sphere**: 3D spheres with volume and surface area calculations
- **Triangle**: 3D triangles with normal calculations
- **Capsule**: 3D capsules for collision detection

### Transformations
- Combined position, rotation, and scale operations
- Matrix generation from transformation components
- Easy manipulation of 3D object transformations

### Colors
- RGB/RGBA color representation
- HEX color conversion
- Color interpolation
- Component-wise operations

### Utilities
- **Random**: Random number generation, unit sphere/circle sampling
- **Interpolation**: Linear, smoothstep, smootherstep, Catmull-Rom interpolation
- **Intersection**: Comprehensive collision detection and intersection testing
- **Math functions**: Trigonometry, clamping, lerping, and more

## Mathematical Constants

The library provides commonly used mathematical constants:

```cpp
MathConstants::PI        // 3.14159265358979323846f
MathConstants::PI_2      // 1.57079632679489661923f
MathConstants::PI_4      // 0.785398163397448309616f
MathConstants::TAU       // 6.28318530717958647692f
MathConstants::E         // 2.71828182845904523536f
MathConstants::SQRT2     // 1.41421356237309504880f
MathConstants::SQRT3     // 1.73205080756887729352f
MathConstants::DEG_TO_RAD
MathConstants::RAD_TO_DEG
```

## Usage

### Basic Example

```cpp
#include <RetMath.hpp>

int main() {
    using namespace Math;
    
    // Vector operations example
    Vector3<float> vector(1.0f, 2.0f, 3.0f);
    Vector3<float> normalized = vector.normalized();  // Get normalized vector
    float length = vector.length();  // Calculate vector length
    
    // Matrix operations - create transformation matrices
    // Create translation matrix for moving objects in 3D space
    Matrix4x4<float> transform = Matrix4x4<float>::translation(1.0f, 2.0f, 3.0f);
    
    // Create rotation matrix for 45 degrees around Y-axis
    // Convert degrees to radians using constant
    Matrix4x4<float> rotation = Matrix4x4<float>::rotationY(MathConstants::PI / 4.0f);
    
    // Combine translation and rotation matrices (translation first, then rotation)
    Matrix4x4<float> combined = transform * rotation;
    
    // Quaternion operations - alternative to matrices for rotations
    Vector3<float> axis(0.0f, 1.0f, 0.0f);  // Rotation axis (Y-axis)
    Quaternion<float> quaternion;
    
    // Create quaternion from axis and angle (90 degrees around Y-axis)
    quaternion.fromAxisAngle(axis, MathConstants::PI / 2.0f);
    
    // Convert quaternion to matrix for use with standard transformation pipeline
    Matrix4x4<float> rotationMatrix = quaternion.toMatrix();
    
    // Geometry operations - working with 3D shapes
    // Create sphere at origin with radius 5 units
    Sphere<float> sphere(Vector3<float>(0.0f, 0.0f, 0.0f), 5.0f);
    
    // Check if point (1, 0, 0) is inside the sphere
    bool contains = sphere.contains(Vector3<float>(1.0f, 0.0f, 0.0f));
    
    return 0;  // Exit program successfully
}
```

### Building the Library

RetMath uses CMake for building. The library can be built as both static and shared libraries:

```bash
mkdir build
cd build
cmake ..
# For multi-config generators (Visual Studio, Xcode)
cmake --build . --config Release

# For single-config generators (Unix Makefiles)
cmake --build .
# or
make
```

This will generate:
- `RetMath.lib` - Static library
- `RetMath.dll` - Shared library (Windows)

### CMake Integration

To use RetMath in your CMake project:

```cmake
# Option 1: Include as subdirectory
add_subdirectory(path/to/RetMath)
target_link_libraries(your_project RetMath_static)

# Option 2: Use as header-only
include_directories(path/to/RetMath/include)
# No linking required
```

## Documentation

Comprehensive documentation is available in the [docs/RetMath](docs/index.html) directory, including:

- Detailed API reference for all classes and functions
- Usage examples for each component
- Mathematical explanations and formulas
- Code samples demonstrating common operations

## Architecture

The library is organized into logical modules:

```
core/RetMath/
├── include/              # Public headers
│   ├── RetMath.hpp       # Main include file
│   ├── vectors/          # Vector classes
│   ├── matrices/         # Matrix classes
│   ├── quaternions/      # Quaternion classes
│   ├── geometry/         # Geometry classes
│   ├── transformations/  # Transformation classes
│   ├── color/            # Color classes
│   └── utilities/        # Utility functions
```

## Performance

- Uses C++20 features for optimal performance
- Template-based design for type safety and flexibility
- Inline functions for critical operations
- SIMD-ready data structures
- Optimized for real-time applications

## Dependencies
RetMath is a **header-only** library with minimal dependencies:
- C++20 compliant compiler
- Standard Template Library (STL)

*Note: For advanced builds, CMake 3.15+ is recommended.*

## License

Released under the MIT License. See [LICENSE](LICENSE) file for details.

## Contributing

Contributions are welcome! Please follow these guidelines:

1. Maintain consistent code style
2. Add comprehensive tests for new features
3. Update documentation for changes
4. Ensure backward compatibility
5. Optimize for performance

## Support

For issues, questions, or feature requests, please use the project's issue tracker.

---

© 2025 retti ❤️
