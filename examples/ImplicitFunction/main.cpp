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
#include "ImplicitShape.h"
#include "Instance.h"

World create_tori_scene()
{
    World world;
    
    // Create floor
    auto material_floor = std::make_shared<Lambertian>(Color(0.7)); 
    auto floor = std::make_shared<Box>(Vec3(100,100,100), material_floor);
    auto floor_translated = Translation::create(floor, Vec3(0,-100-1.3,0));
    world.add(floor_translated);

    auto material = std::make_shared<Lambertian>(Color(0.7,0.7,0.7));

    double radius_major = 1;
    double radius_minor = 0.2;

    auto torus = std::make_shared<Torus>(radius_major, radius_minor, material);
    auto torus2 = Rotation::create(torus, Basis().rotate(Vec3(0,0,1), degrees_to_radians(90)));
    auto torus3 = Rotation::create(torus, Basis().rotate(Vec3(1,0,0), degrees_to_radians(90)));

    auto bool_torus1 = std::make_shared<BoolOp>(BoolOp::merge, torus, torus2);
    auto bool_torus2 = std::make_shared<BoolOp>(BoolOp::merge, bool_torus1, torus3);

    // Add merged tori to the world
    world.add(Translation::create(bool_torus2, Vec3(1.3*2,0,0)));

    // Add unmerged tori to the world (produces shadow acne)
    world.add(torus);
    world.add(torus2);
    world.add(torus3);

    return world;
}

// Reproduces image on https://en.wikipedia.org/wiki/Constructive_solid_geometry
World create_csg_scene()
{
    World world;

    // Create checkered floor
    auto texture_floor = std::make_shared<CheckerTexture>(Color(1), Color(0));
    auto material_floor = std::make_shared<Lambertian>(texture_floor); 
    auto floor = std::make_shared<Box>(Vec3(100,100,100), material_floor);
    auto floor_translated = Translation::create(floor, Vec3(0,-100-1.3,0));
    world.add(floor_translated);

    // Create materials
    auto material_red = std::make_shared<Lambertian>(Color(1,0,0));
    auto material_green = std::make_shared<Lambertian>(Color(0,1,0));
    auto material_blue = std::make_shared<Lambertian>(Color(0,0,1));

    // Create the 3 cylinders and orientate them
    auto cylinder = std::make_shared<Cylinder>(2, 0.7, material_green);
    auto cylinder2 = Rotation::create(cylinder, Basis().rotate(Vec3(0,0,1), degrees_to_radians(90)));
    auto cylinder3 = Rotation::create(cylinder, Basis().rotate(Vec3(1,0,0), degrees_to_radians(90)));

    // Merge the cyclinders
    auto bool1 = std::make_shared<BoolOp>(BoolOp::merge, cylinder, cylinder2);
    auto bool2 = std::make_shared<BoolOp>(BoolOp::merge, bool1, cylinder3);

    // Create the box and the sphere
    auto box = std::make_shared<Box>(Vec3(1), material_red);
    auto sphere = std::make_shared<Sphere>(1.3,material_blue);

    // Combine the box, sphere, and cylinders
    auto bool3 = std::make_shared<BoolOp>(BoolOp::intersection, box, sphere);
    auto bool_csg = std::make_shared<BoolOp>(BoolOp::subtraction, bool3, bool2);

    world.add(bool_csg);
    return world;
}

Camera create_tori_camera()
{
    Point3 lookfrom(1.3,2,5);
    Point3 lookat(1.3,0,0);
    Vec3 vup(0,1,0);
    Transform transform(lookfrom, lookat, vup);

    CameraSettings camera_settings;
    camera_settings.aspect_ratio = 16.0/9.0;
    camera_settings.vertical_fov = 40;
    const double aperture = 0;
    const double focus_dist = (lookat - lookfrom).length();
    camera_settings.depth_of_field(aperture, focus_dist);
    return Camera(transform, camera_settings);
}

Camera create_csg_camera()
{
    Point3 lookfrom(3,3,3);
    Point3 lookat(0,0,0);
    Vec3 vup(0,1,0);
    Transform transform(lookfrom, lookat, vup);

    CameraSettings camera_settings;
    camera_settings.aspect_ratio = 16.0/9.0;
    camera_settings.vertical_fov = 40;
    const double aperture = 0;
    const double focus_dist = (lookat - lookfrom).length();
    camera_settings.depth_of_field(aperture, focus_dist);
    return Camera(transform, camera_settings);
}

int main()
{
    // Create World
    World tori_scene = create_tori_scene();
    World csg_scene = create_csg_scene();
    
    // Create camera
    Camera camera_tori = create_tori_camera();
    Camera camera_csg = create_csg_camera();
    
    // Capture scene
    RenderSettings render_settings;
    render_settings.samples_per_pixel = 100;
    render_settings.image_width = 400;
    render_settings.max_ray_collisions = 40;
    Image image_tori = camera_tori.get_image(tori_scene, render_settings);
    Image image_csg = camera_csg.get_image(csg_scene, render_settings);

    // Save images to files
    image_tori.save_image("tori.ppm");
    image_csg.save_image("csg.ppm");

    return 0;
}