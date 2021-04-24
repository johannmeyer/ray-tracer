#include <iostream>

#include "Hittable.h"
#include "Image.h"
#include "Vec3.h"
#include "Utility.h"
#include "World.h"
#include "Sphere.h"
#include "Camera.h"
#include "Material.h"

int main()
{
    // Create Materials
    auto material_ground = std::make_shared<Lambertian>(Color(0.8, 0.8, 0.0));
    auto material_center = std::make_shared<Dielectric>(Color(1,0,0), 1.5);
    auto material_left   = std::make_shared<Dielectric>(Color(1,1,1), 1.5);
    auto material_right  = std::make_shared<Metal>(Color(0.8, 0.6, 0.2), 1);

    // Create world
    World world;
    world.add(std::make_shared<Sphere>(Point3( 0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(std::make_shared<Sphere>(Point3( 0.0,    0.0, -1.0),   0.5, material_center));
    world.add(std::make_shared<Sphere>(Point3(-1.0,    0.0, -1.0),   0.5, material_left));
    world.add(std::make_shared<Sphere>(Point3( 1.0,    0.0, -1.0),   0.5, material_right));
    
    // Create camera
    Camera camera;
    
    // Capture scene
    const int image_width = 400;
    Image image = camera.get_image(image_width, world);

    // Save images to files
    image.save_image("out.ppm");
    Image ascii_image = image.to_ascii_image();
    ascii_image.save_image("ascii.ppm");

    return 0;
}