cmake_minimum_required(VERSION 3.10)
project(CppToJavaCompiler)

# Set C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find Python3
find_package(Python3 REQUIRED COMPONENTS Interpreter)

# Enable testing
enable_testing()

# Use CMake's FetchContent to download GoogleTest
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(googletest)

# Add source and test directories
add_subdirectory(src)
add_subdirectory(tests)
