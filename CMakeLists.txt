cmake_minimum_required(VERSION 3.20)

project(aether)

set(CMAKE_CXX_STANDARD 26)

# --------------------
# Core library (NO main.cpp)
# --------------------
add_library(core STATIC
    src/validation.cpp
    src/errors.cpp
    src/compiler.cpp
    src/lexer.cpp
    src/token.cpp
)

target_include_directories(core PUBLIC include)

# --------------------
# Main executable
# --------------------
add_executable(aether
    src/main.cpp
)

target_link_libraries(aether PRIVATE core)

# --------------------
# Testing
# --------------------
include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.2
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(run_tests
    tests/test_errors.cpp
	tests/test_validation.cpp
	tests/test_token.cpp
    tests/test_lexer.cpp
)

target_link_libraries(run_tests
    PRIVATE core
    gtest_main
)

add_test(NAME ErrorTestSuite COMMAND run_tests)
add_test(NAME ValidationTestSuite COMMAND run_tests)
add_test(NAME TokenTestSuite COMMAND run_tests)
add_test(NAME LexerTestSuite COMMAND run_tests)
