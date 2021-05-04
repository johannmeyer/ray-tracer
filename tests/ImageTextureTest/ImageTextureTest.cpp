#include "Hittable.h"
#include "Image.h"
#include "Vec3.h"
#include "Utility.h"
#include "World.h"
#include "Sphere.h"
#include "Camera.h"
#include "Material.h"
#include "Texture.h"

Camera create_camera()
{
    Point3 lookfrom(13,2,3);
    Point3 lookat(0,0,0);
    Vec3 vup(0,1,0);
    Orientation orientation(lookfrom, lookat, vup);

    CameraSettings camera_settings;
    camera_settings.aspect_ratio = 3.0/2.0;
    camera_settings.vertical_fov = 10;
    const double aperture = 0;
    const double focus_dist = (lookat - lookfrom).length();
    camera_settings.depth_of_field(aperture, focus_dist);
    return Camera(orientation, camera_settings);
}

int main()
{
    // Create image texture material
    auto material_sphere =  std::make_shared<Lambertian>("earthmap.ppm");

    // Create world
    World world;
    world.add(std::make_shared<Sphere>(Point3(0,0,0), 1, material_sphere));

    // Create camera
    Camera camera = create_camera();
    
    // Capture scene
    RenderSettings render_settings;
    render_settings.samples_per_pixel = 100;
    Image image = camera.get_image(world, render_settings);

    // Save images to files
    image.save_image("out.ppm");
    Image ascii_image = image.to_ascii_image();
    ascii_image.save_image("ascii.ppm");

    return 0;
}