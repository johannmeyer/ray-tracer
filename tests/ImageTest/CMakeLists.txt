add_executable(ImageTest ImageTest.cpp)
target_link_libraries(ImageTest RayTracer)

configure_file(checksum.txt checksum.txt COPYONLY)
add_test(ImageTest ${TEST_SCRIPT} ImageTest)