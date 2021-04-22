#include <iostream>

#include "Hittable.h"
#include "Image.h"
#include "Vec3.h"
#include "Utility.h"
#include "World.h"
#include "Sphere.h"
#include "Camera.h"

int main()
{
    // Create world
    World world;
    world.add(std::make_shared<Sphere>(Point3(0,0,-1), 0.5));
    world.add(std::make_shared<Sphere>(Point3(0,-100.5,-1), 100));
    
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