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
    auto material_center = std::make_shared<Lambertian>(Color(0.1, 0.2, 0.5));
    auto material_left   = std::make_shared<Dielectric>(Color(1,1,1), 1.5);
    auto material_right  = std::make_shared<Metal>(Color(0.8, 0.6, 0.2), 0);

    // // Create world
    World world;
    world.add(std::make_shared<Sphere>(Point3( 0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(std::make_shared<Sphere>(Point3( 0.0,    0.0, -1.0),   0.5, material_center));
    world.add(std::make_shared<Sphere>(Point3(-1.0,    0.0, -1.0),   0.5, material_left));
    world.add(std::make_shared<Sphere>(Point3(-1.0,    0.0, -1.0), -0.45, material_left));
    world.add(std::make_shared<Sphere>(Point3( 1.0,    0.0, -1.0),   0.5, material_right));

    
    // auto R = cos(PI/4);
    // World world;

    // auto material_left  = std::make_shared<Lambertian>(Color(0,0,1));
    // auto material_right = std::make_shared<Lambertian>(Color(1,0,0));

    // world.add(std::make_shared<Sphere>(Point3(-R, 0, -1), R, material_left));
    // world.add(std::make_shared<Sphere>(Point3( R, 0, -1), R, material_right));
    
    // Create camera
    Point3 lookfrom(3,3,2);
    Point3 lookat(0,0,-1);
    Vec3 vup(0,1,0);
    Orientation orientation(lookfrom, lookat, vup);

    CameraSettings camera_settings;
    camera_settings.vertical_fov = 20;
    camera_settings.depth_of_field(2.0, (lookfrom - lookat).length());
    Camera camera(orientation, camera_settings);
    
    // Capture scene
    RenderSettings render_settings;
    // render_settings.image_width = 1000;
    Image image = camera.get_image(world, render_settings);

    // Save images to files
    image.save_image("out.ppm");
    Image ascii_image = image.to_ascii_image();
    ascii_image.save_image("ascii.ppm");

    return 0;
}