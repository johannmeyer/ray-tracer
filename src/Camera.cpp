#include "Camera.h"
#include "Utility.h"


Camera::Camera(const Orientation& orientation, const CameraSettings& camera_settings) :
    orientation(orientation),
    aspect_ratio(camera_settings.aspect_ratio)
{
    double theta = degrees_to_radians(camera_settings.vertical_fov);
    double h = std::tan(theta/2.0);

    double viewport_height = 2.0 * h;
    double viewport_width = aspect_ratio * viewport_height;

    this->orientation.to_cam_basis();

    horizontal = camera_settings.focus_dist * viewport_width * this->orientation.basis.x; // positive right
    vertical = camera_settings.focus_dist * viewport_height * this->orientation.basis.y; // positive down
    top_left_corner = orientation.origin - horizontal/2 - vertical/2 + camera_settings.focus_dist*this->orientation.basis.z;

    lens_radius = camera_settings.aperture/2;
}

Ray Camera::get_ray(double u, double v) const
{
    Vec3 perturbation = lens_radius * Vec3::random_in_unit_circle();
    Vec3 offset = orientation.origin + orientation.basis.x*perturbation.x() + orientation.basis.y*perturbation.y();
    return Ray(offset, top_left_corner + u*horizontal + v*vertical - offset);
}

Image Camera::get_image(World world, const RenderSettings& render_settings) const
{
    // Load render settings
    const int samples_per_pixel = render_settings.samples_per_pixel;
    const int max_ray_collisions = render_settings.max_ray_collisions;
    const int image_cols = render_settings.image_width;

    const int image_rows = static_cast<int>(image_cols / aspect_ratio);
    Image image(image_rows, image_cols);

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
