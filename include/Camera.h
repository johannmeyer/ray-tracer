#ifndef CAMERA_H
#define CAMERA_H

#include "Vec3.h"
#include "Ray.h"
#include "Image.h"
#include "World.h"
#include "RenderSettings.h"
#include "Orientation.h"
#include "CameraSettings.h"

class Camera
{
    private:
        Orientation orientation;
        Point3 top_left_corner;
        Vec3 horizontal;
        Vec3 vertical;
        double aspect_ratio;
        double lens_radius;

    public:
        Camera(const Orientation& orientation, const CameraSettings& camera_settings);
        
        Ray get_ray(double u, double v) const;

        Image get_image(World world, const RenderSettings& render_settings) const;
};

#endif