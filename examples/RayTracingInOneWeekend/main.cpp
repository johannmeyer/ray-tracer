#include <iostream>

#include "Hittable.h"
#include "Image.h"
#include "Vec3.h"
#include "Utility.h"
#include "World.h"
#include "Camera.h"
#include "Material.h"
#include "Texture.h"
#include "BVH.h"
#include "Instance.h"

World create_scene()
{
    World world_objects;
    auto material_ground = std::make_shared<Lambertian>(Color(0.5)); 
    auto ground = std::make_shared<Sphere>(1000.0, material_ground);
    world_objects.add(Translation::create(ground, Point3( 0.0, -1000, 0.0)));

    auto material_dielectric = std::make_shared<Dielectric>(Color(1,1,1), 1.5);
    auto sphere_dielectric = std::make_shared<Sphere>(1.0, material_dielectric);
    world_objects.add(Translation::create(sphere_dielectric, Point3(0, 1, 0)));

    auto material_lambertian = std::make_shared<Lambertian>(Color(0.4, 0.2, 0.1));
    auto sphere_lambertian = std::make_shared<Sphere>(1.0, material_lambertian);
    world_objects.add(Translation::create(sphere_lambertian, Point3(-4, 1, 0)));

    auto material_metal = std::make_shared<Metal>(Color(0.7, 0.6, 0.5), 0.0);
    auto sphere_metal = std::make_shared<Sphere>(1.0, material_metal);
    world_objects.add(Translation::create(sphere_metal, Point3(4, 1, 0)));

    for (int i = -11; i < 11; i++)
    {
        for (int j = -11; j < 11; j++)
        {
            Point3 center(i + 0.9*random_double(), 0.2, j + 0.9*random_double());
            if ((center - Point3(4, 0.2, 0)).length() > 0.9)
            {
                std::shared_ptr<Material> material;

                double rand_material = random_double();
                if (rand_material < 0.8)
                {
                    //diffuse
                    Color albedo = Color::random() * Color::random();
                    material = std::make_shared<Lambertian>(albedo);
                }
                else if (rand_material < 0.95)
                {
                    Color albedo = Color::random(0.5, 1);
                    double roughness = random_double(0, 0.5);
                    material = std::make_shared<Metal>(albedo, roughness); 
                }
                else
                {
                    material = material_dielectric;
                }
                auto sphere = std::make_shared<Sphere>(0.2, material);
                world_objects.add(Translation::create(sphere, center));
            }
        }
    }
    // store it in a BVH Tree for faster ray collision testing
    World world;
    world.add(BVHNode::create(world_objects));
    return world;
}

Camera create_camera()
{
    Point3 lookfrom(13,2,3);
    Point3 lookat(0,0,0);
    Vec3 vup(0,1,0);
    Transform transform(lookfrom, lookat, vup);

    CameraSettings camera_settings;
    camera_settings.aspect_ratio = 3.0/2.0;
    camera_settings.vertical_fov = 20;
    const double aperture = 0.1;
    const double focus_dist = 10;
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
    render_settings.max_ray_collisions = 50;
    Image image = camera.get_image(world, render_settings);

    // Save images to files
    image.save_image("RayTracingInOneWeekend.ppm");
    
    return 0;
}