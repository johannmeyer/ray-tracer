# Ray Tracer in C++

This project is based off the code from the Ray Tracing in One Weekend Series. The code structure has been changed to cleanup the main file and avoid implementation details in the main file. Moreover, the output is directly written to file and does not require output redirection to a file in the console. An ASCII renderer was also implemented.

# ASCII Renderer

The ASCII renderer converts the images to look like a color ASCII image. The original image is divided into a coarser grid based on the dimensions of the ASCII characters. The mean intensity of the colors in the coarse grid are used to determine which ASCII character should be used for that block. Each pixel in the block can then in parallel draw itself by looking up the Boolean value of the ASCII character's array (see ASCII.h). The original color of the image is returned by using the mean color and multiplying it by the Boolean value.

The implementation converts the image in a block-by-block approach opposed to a scanline approach to improve cache locality, data reuse, and parallelisability.

![ASCII Image](<./output-images/ascii.png>)

## Example
```cpp
#include "Image.h"

Image ascii_image = image.to_ascii_image();
ascii_image.save_image("ascii.ppm");
```

# Creating Materials
At present, three materials have been added: Lambertian (diffuse), Metal, and Dielectric. All materials require the albedo to be specified. Metal has an additional roughness parameter and Dielectrics require the index of refraction to be specified. The index of refraction of glass is between 1.3 and 1.7.

![Metal and Lambertian Spheres](<./output-images/Metal and Lambertian Spheres.png>)

## Example
```cpp
#include "Material.h"

auto material_lambertian = std::make_shared<Lambertian>(Color(0.8, 0.8, 0.0));
auto material_metal = std::make_shared<Metal>(Color(0.8, 0.8, 0.8), 0.3);
auto material_dielectric   = std::make_shared<Dielectric>(Color(1,1,1), 1.5);
```

## Textures
Textures have currently been implemented for Lambertian materials only. 

Implemented textures:
* SolidColor
* CheckerTexture
* ImageTexture*

*Image textures must be in uncompressed `.ppm` format (P3).

![Image Texture](<./output-images/Image Texture.png>)

```cpp
// Create image texture material
auto material_sphere =  std::make_shared<Lambertian>("earthmap.ppm");

// Or to share textures between objects
auto image_texture = std::make_shared<ImageTexture>("earthmap.ppm");
auto material_sphere =  std::make_shared<Lambertian>(image_texture);
```

# Creating a Scene (World) and Adding Objects
A world must be created and then each object should be added to the world. Currently, only spheres can be added to the world. Objects have a position, a size, and a material.

## Example
```cpp
#include "World.h"
#include "Material.h"
#include "Sphere.h"
#include "Vec3.h"

World world;

// Add Lambertian sphere to world
const Point3 position = Point3(0.0, 0.0, -1.0);
const double radius = 0.5;
auto material = std::make_shared<Lambertian>(Color(0.8, 0.8, 0.0));
world.add(std::make_shared<Sphere>(position, radius, material));
```

## Hollow Objects
Hollow objects can be created using dielectric materials with a negative radius at the same position as another dielectric material.

```cpp
Point3 position(0.0, 0.0, -1.0);
const double outer_radius = 0.5;
const double inner_radius = -0.4; // note negative sign
world.add(std::make_shared<Sphere>(position, outer_radius, material_dielectric));
world.add(std::make_shared<Sphere>(position, inner_radius, material_dielectric));
```

# Creating a Camera and Ray Tracing the World
To ray trace a scene, a camera needs to be added. The call to `get_image()` rasterises the world scene and performs the ray tracing. The images are gamma corrected ($\gamma$=2) when they are saved to a `.ppm` file. The images are ray traced with stochastic ray positions within a pixel and thus results in a nice antialiased image. However, due to the stochasticity in ray bounces, the images require large amounts of samples per pixel to avoid noisy images. `CameraSettings` and `RenderSettings` are used to reduce the number of parameters required to create a camera and render a scene and provide some defaults for parameters.

## Example
```cpp
#include "Camera.h"
#include "Image.h"

// Set camera position and orientation
Point3 lookfrom(13,2,3);
Point3 lookat(0,0,0);
Vec3 vup(0,1,0);
Orientation orientation(lookfrom, lookat, vup);

// Set camera settings
CameraSettings camera_settings;
camera_settings.aspect_ratio = 3.0/2.0;
camera_settings.vertical_fov = 20;
const double aperture = 0.1;
const double focus_dist = 10.0;
camera_settings.depth_of_field(aperture, focus_dist);

// Create camera
Camera camera(orientation, camera_settings);

// Capture scene
RenderSettings render_settings;
render_settings.samples_per_pixel = 500;
Image image = camera.get_image(world, render_settings);

// Save images to files
image.save_image("ray-traced-image.ppm");
```