cmake_minimum_required(VERSION 3.13)

project(RayTracer)

# C++11 to get some newer features like move semantics etc
set (CMAKE_CXX_STANDARD 11)

# This helps find bugs and leads to better code in general
# lots of warnings and all warnings as errors. -march=native
# resulted in marginally worse performance.
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-Wall -Wextra -pedantic -Werror -Wconversion)
    message(STATUS "Hello World: ${CMAKE_BUILD_TYPE}")
    if(CMAKE_BUILD_TYPE STREQUAL "Release" OR CMAKE_BUILD_TYPE STREQUAL "DebugOptimised")
        add_compile_options(-O3 -ffast-math) # optimisations in code (disable for debugging)
    endif()

    if(CMAKE_BUILD_TYPE STREQUAL "Release")
        add_compile_options(-DNDEBUG) # remove asserts
    endif()
endif()

# Header files
include_directories(include)

add_library(RayTracer "")

add_subdirectory(src)

# Examples
add_subdirectory(examples)

# Test suite (Checksums and scripts only work on Linux)
enable_testing()
add_subdirectory(tests)