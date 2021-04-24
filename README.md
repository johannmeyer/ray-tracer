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
At present, two materials have been added: Lambertian (diffuse) and Metal. Both materials require the albedo to be specified. Metal has an additional roughness parameter.

![Metal and Lambertian Spheres](<./output-images/Metal and Lambertian Spheres.png>)

## Example
```cpp
#include "Material.h"

auto material_lambertian = std::make_shared<Lambertian>(Color(0.8, 0.8, 0.0));
auto material_metal = std::make_shared<Metal>(Color(0.8, 0.8, 0.8), 0.3);
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

# Creating a Camera and Ray Tracing the World
To ray trace a scene, a camera needs to be added. The position and orientation of the camera is currently fixed. The call to `get_image()` rasterises the world scene and performs the ray tracing. The images are gamma corrected ($\gamma$=2) when they are saved to a `.ppm` file. The images are ray traced with stochastic ray positions within a pixel and thus results in a nice antialiased image. However, due to the stochasticity in ray bounces, the images require large amounts of samples per pixel to avoid noisy images.

## Example
```cpp
#include "Camera.h"
#include "Image.h"

// Create camera
Camera camera;

// Capture scene
const int image_width = 400;
Image image = camera.get_image(image_width, world);

// Save images to files
image.save_image("ray-traced-image.ppm");
```