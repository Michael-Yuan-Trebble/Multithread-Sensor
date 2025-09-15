cmake_minimum_required (VERSION 3.8)

project ("Multithreaded Sim")

# C++ 17 Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_CLANG_TIDY
    "clang-tidy;-checks=*;-header-filter=.*;-line-filter=[{\"name\": \".*Test.cpp\"}]")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Main Executable
add_executable (CMakeTarget "Multithreaded Sim.cpp" "Multithreaded Sim.h")

# GoogleTest Setup
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Enable CTest
enable_testing()

# Testing Subdirectory
add_subdirectory(test)