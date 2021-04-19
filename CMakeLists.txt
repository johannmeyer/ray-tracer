

project(RayTracer)

# C++11 to get some newer features like move semantics etc
set (CMAKE_CXX_STANDARD 11)

# This helps find bugs and leads to better code in general
# lots of warnings and all warnings as errors
add_compile_options(-Wall -Wextra -pedantic -Werror)

# C++11 to get some newer features like move semantics etc
set (CMAKE_CXX_STANDARD 11)

# Header files
include_directories(include)

set(SRCS src/Image.cpp)

# add_executable(RayTracer src/main.cpp ${SRCS})
add_executable(ImageTest tests/ImageTest/ImageTest.cpp ${SRCS})


# enable_testing()
# add_test(ImageTest diff ImageTest.ppm ${PROJECT_SOURCE_DIR}/tests/ImageTest/golden_reference.ppm)