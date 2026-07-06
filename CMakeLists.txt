cmake_minimum_required(VERSION 4.3.1)

project(aether)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_EXTENSIONS OFF)

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

target_sources(core
    PUBLIC FILE_SET HEADERS
        BASE_DIRS include
)

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

include(GoogleTest)
gtest_discover_tests(run_tests)
