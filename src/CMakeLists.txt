add_subdirectory(ImplicitShape)
add_subdirectory(Material)
add_subdirectory(Texture)

target_sources(RayTracer PRIVATE
    AABB.cpp
    BVH.cpp 
    Camera.cpp 
    Image.cpp 
    World.cpp)