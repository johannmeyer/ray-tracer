#include "Camera.h"
#include "Utility.h"

Camera::Camera()
{
    aspect_ratio = 16.0/9.0;
    double viewport_height = 2.0;
    double viewport_width = aspect_ratio * viewport_height;
    double focal_length = 1.0;

    origin = Point3(0,0,0);
    horizontal = Vec3(viewport_width, 0, 0);
    vertical = Vec3(0,viewport_height, 0);
    top_left_corner = origin - horizontal/2 + vertical/2 - Vec3(0, 0, focal_length);
}

Ray Camera::get_ray(double u, double v) const
{
    return Ray(origin, top_left_corner + u*horizontal - v*vertical - origin);
}

Image Camera::get_image(int image_cols, World world, const bool antialiasing) const
{
    const int max_ray_collisions = 50;

    const int image_rows = static_cast<int>(image_cols / aspect_ratio);
    Image image(image_rows, image_cols);
    
    int samples_per_pixel = 1;
    if (antialiasing) samples_per_pixel = 100;

    for (int r = 0; r < image_rows; r++)
    {
        for (int c = 0; c < image_cols; c++)
        {
            Color pixel_color(0,0,0);
            for (int s = 0; s < samples_per_pixel; s++)
            {
                double u = (double(c) + random_double())/ (image_cols-1);
                double v = (double(r) + random_double())/ (image_rows-1);
                Ray ray = get_ray(u,v);
                pixel_color += world.get_ray_color(ray, max_ray_collisions);
            }
            image.set(r, c, pixel_color/samples_per_pixel);
        }
        std::cerr << r*100/image_rows << "% complete" << std::endl;
    }
    return image;
}
