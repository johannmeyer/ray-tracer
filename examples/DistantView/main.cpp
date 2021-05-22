#include <iostream>

#include "Hittable.h"
#include "Image.h"
#include "Vec3.h"
#include "Utility.h"
#include "World.h"
#include "Camera.h"
#include "Material.h"
#include "Instance.h"

World create_scene()
{
    World world;
    auto material_ground = std::make_shared<Lambertian>(Color(0.8, 0.8, 0.0));
    auto material_center = std::make_shared<Lambertian>(Color(0.1, 0.2, 0.5));
    auto material_left   = std::make_shared<Dielectric>(Color(1), 1.5);
    auto material_right  = std::make_shared<Metal>(Color(0.8, 0.6, 0.2), 0.0);

    auto ground = Translation::create(std::make_shared<Sphere>(100.0, material_ground), Point3(0.0, -100.5, -1.0));
    auto center = Translation::create(std::make_shared<Sphere>(0.5, material_center), Point3(0.0, 0.0, -1.0));
    auto left = Translation::create(std::make_shared<Sphere>(0.5, material_left), Point3(-1.0, 0.0, -1.0));
    auto left_hollow = Translation::create(std::make_shared<Sphere>(-0.45, material_left), Point3(-1.0, 0.0, -1.0));
    auto right = Translation::create(std::make_shared<Sphere>(0.5, material_right),Point3(1.0, 0.0, -1.0));
    
    world.add(ground);
    world.add(center);
    world.add(left);
    world.add(left_hollow);
    world.add(right);

    return world;
}

Camera create_camera()
{
    Point3 lookfrom(-2,2,1);
    Point3 lookat(0,0,-1);
    Vec3 vup(0,1,0);
    Transform transform(lookfrom, lookat, vup);

    CameraSettings camera_settings;
    camera_settings.aspect_ratio = 16.0/9.0;
    camera_settings.vertical_fov = 90;
    const double aperture = 0;
    const double focus_dist = (lookfrom-lookat).length();
    camera_settings.depth_of_field(aperture, focus_dist);
    return Camera(transform, camera_settings);
}

int main()
{
    // Create World
    World world = create_scene();

    // Create camera
    Camera camera = create_camera();
    
    // Capture scene
    RenderSettings render_settings;
    render_settings.samples_per_pixel = 100;
    render_settings.image_width = 400;
    render_settings.max_ray_collisions = 100;
    Image image = camera.get_image(world, render_settings);

    // Save images to files
    image.save_image("DistantView.ppm");
    
    return 0;
}