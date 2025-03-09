cmake_minimum_required(VERSION 3.10)
project(CppToJavaCompiler)

set(CMAKE_CXX_STANDARD 17)

# Glob all source files
file(GLOB SRC_FILES
    ${CMAKE_SOURCE_DIR}/src/*.cpp
    ${CMAKE_SOURCE_DIR}/src/lexer/*.cpp
    ${CMAKE_SOURCE_DIR}/src/parser/*.cpp
    ${CMAKE_SOURCE_DIR}/src/codegen/*.cpp
    ${CMAKE_SOURCE_DIR}/src/utils/*.cpp
)

# Ensure there are source files
if(NOT SRC_FILES)
    message(FATAL_ERROR "No source files found. Check file paths.")
endif()

# Include directories for headers
include_directories(
    ${CMAKE_SOURCE_DIR}/src/lexer
    ${CMAKE_SOURCE_DIR}/src/parser
    ${CMAKE_SOURCE_DIR}/src/codegen
    ${CMAKE_SOURCE_DIR}/src/utils
)

# Define the executable
add_executable(CppToJavaCompiler ${SRC_FILES})

# Set compile options
target_compile_options(CppToJavaCompiler PRIVATE -pthread -static-libgcc -static-libstdc++)

# Link required libraries
find_package(Threads REQUIRED)
target_link_libraries(CppToJavaCompiler PRIVATE Threads::Threads)
