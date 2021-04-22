cmake_minimum_required(VERSION 3.10)

project(RayTracer)

# C++11 to get some newer features like move semantics etc
set (CMAKE_CXX_STANDARD 11)

# This helps find bugs and leads to better code in general
# lots of warnings and all warnings as errors. -march=native
# resulted in marginally worse performance.
add_compile_options(-O3 -Wall -Wextra -pedantic -Werror -ffast-math)

# C++11 to get some newer features like move semantics etc
set (CMAKE_CXX_STANDARD 11)

# Header files
include_directories(include)

set(SRCS src/Image.cpp src/Sphere.cpp src/World.cpp src/Camera.cpp)

add_executable(RayTracer src/main.cpp ${SRCS})
add_executable(ImageTest tests/ImageTest/ImageTest.cpp ${SRCS})

# enable_testing()
# add_test(ImageTest diff ImageTest.ppm ${PROJECT_SOURCE_DIR}/tests/ImageTest/golden_reference.ppm)