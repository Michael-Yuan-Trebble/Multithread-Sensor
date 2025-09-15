cmake_minimum_required (VERSION 3.8)

# Add Test Execs
add_executable(TESTS test_main.cpp SensorUtils.h)

# Link GoogleTest
target_link_libraries(TESTS gtest_main)

# Auto discover tests
include(GoogleTest)
gtest_discover_tests(TESTS)