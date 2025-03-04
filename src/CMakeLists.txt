# Glob all existing source files
file(GLOB SRC_FILES
    ${CMAKE_SOURCE_DIR}/src/*.cpp
    ${CMAKE_SOURCE_DIR}/src/lexer/*.cpp
)

# Ensure there are source files
if(NOT SRC_FILES)
    message(FATAL_ERROR "No source files found. Check file paths.")
endif()

# Define the executable
add_executable(CppToJavaCompiler ${SRC_FILES})

# Set compile options
target_compile_options(CppToJavaCompiler PRIVATE -pthread -static-libgcc -static-libstdc++)

# Link required libraries
find_package(Threads REQUIRED)
target_link_libraries(CppToJavaCompiler PRIVATE Threads::Threads)
