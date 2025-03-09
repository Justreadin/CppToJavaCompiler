cmake_minimum_required(VERSION 3.10)
project(CppToJavaCompiler)

# Set C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Enable testing (Optional)
option(ENABLE_TESTS "Enable unit tests" ON)

# Fetch GoogleTest
if (ENABLE_TESTS)
    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    )
    FetchContent_MakeAvailable(googletest)
endif()

# Add source and test directories
add_subdirectory(src)

if (ENABLE_TESTS)
    add_subdirectory(tests)
endif()
