#include <iostream>

#include "Hittable.h"
#include "Image.h"
#include "Vec3.h"
#include "Utility.h"
#include "World.h"
#include "Sphere.h"
#include "Camera.h"
#include "Material.h"

World create_scene()
{
    World world;
    auto material_ground = std::make_shared<Lambertian>(Color(0.5, 0.5, 0.5)); 
    world.add(std::make_shared<Sphere>(Point3( 0.0, -1000, 0.0), 1000.0, material_ground));

    auto material1 = std::make_shared<Dielectric>(Color(1,1,1), 1.5);
    world.add(std::make_shared<Sphere>(Point3(0, 1, 0), 1.0, material1));

    auto material2 = std::make_shared<Lambertian>(Color(0.4, 0.2, 0.1));
    world.add(std::make_shared<Sphere>(Point3(-4, 1, 0), 1.0, material2));

    auto material3 = std::make_shared<Metal>(Color(0.7, 0.6, 0.5), 0.0);
    world.add(std::make_shared<Sphere>(Point3(4, 1, 0), 1.0, material3));

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
                    material = std::make_shared<Dielectric>(Color(1,1,1), 1.5);
                }
                world.add(std::make_shared<Sphere>(center, 0.2, material));
            }
        }
    }
    return world;
}

Camera create_camera()
{
    Point3 lookfrom(13,2,3);
    Point3 lookat(0,0,0);
    Vec3 vup(0,1,0);
    Orientation orientation(lookfrom, lookat, vup);

    CameraSettings camera_settings;
    camera_settings.aspect_ratio = 3.0/2.0;
    camera_settings.vertical_fov = 20;
    const double aperture = 0.1;
    const double focus_dist = 10.0;
    camera_settings.depth_of_field(aperture, focus_dist);
    return Camera(orientation, camera_settings);
}

int main()
{
    // Create World
    World world = create_scene();

    // Create camera
    Camera camera = create_camera();
    
    // Capture scene
    RenderSettings render_settings;
    render_settings.samples_per_pixel = 500;
    Image image = camera.get_image(world, render_settings);

    // Save images to files
    image.save_image("out.ppm");
    Image ascii_image = image.to_ascii_image();
    ascii_image.save_image("ascii.ppm");

    return 0;
}