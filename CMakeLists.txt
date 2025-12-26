cmake_minimum_required(VERSION 3.15)
project(RetMath LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_library(RetMath_static STATIC ${SOURCES})
target_include_directories(RetMath_static PUBLIC include)
set_target_properties(RetMath_static PROPERTIES OUTPUT_NAME "RetMath")

add_library(RetMath_shared SHARED ${SOURCES})
target_include_directories(RetMath_shared PUBLIC include)
set_target_properties(RetMath_shared PROPERTIES OUTPUT_NAME "RetMath")

if(MSVC)
    target_compile_options(RetMath_static PRIVATE $<$<CONFIG:Release>:/O2 /Ob2>)
    target_compile_options(RetMath_shared PRIVATE $<$<CONFIG:Release>:/O2 /Ob2>)

    set_target_properties(RetMath_shared PROPERTIES
        WINDOWS_EXPORT_ALL_SYMBOLS ON
    )
endif()

message(STATUS "Building both static (.lib) and shared (.dll) libraries")
