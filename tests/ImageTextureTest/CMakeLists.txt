add_executable(ImageTextureTest ImageTextureTest.cpp)
target_link_libraries(ImageTextureTest RayTracer)

configure_file(checksum.txt checksum.txt COPYONLY)
configure_file(earthmap.ppm earthmap.ppm COPYONLY)

add_test(ImageTextureTest ${TEST_SCRIPT} ImageTextureTest)