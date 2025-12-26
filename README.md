# RetMath - Mathematics Library for Games and Graphics (MIT)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)
[![Documentation](https://img.shields.io/badge/documentation-📘-informational)](docs/)

RetMath is a comprehensive C++ mathematics library designed for game development, computer graphics, and real-time applications. It provides a wide range of mathematical structures and functions for working with vectors, matrices, quaternions, geometry, transformations, colors, and various utility functions.

<div align="center">
  <img src="docs/2dgravity.gif" alt="RetMath Library Demo" width="800"/>
  <br>
  <em>Demonstration of vector operations, matrix transformations, and collision detection</em>
<div>

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
