# Include GoogleTest
include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

# Add test executable
add_executable(CompilerTests test_sample.cpp) # Ensure test_sample.cpp exists

# Link GoogleTest
target_link_libraries(CompilerTests PRIVATE GTest::gtest_main)

# Enable tests
include(GoogleTest)
gtest_discover_tests(CompilerTests)
