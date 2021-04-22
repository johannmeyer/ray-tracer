#ifndef CAMERA_H
#define CAMERA_H

#include "Vec3.h"
#include "Ray.h"
#include "Image.h"
#include "World.h"

class Camera
{
    private:
        Point3 origin;
        Point3 top_left_corner;
        Vec3 horizontal;
        Vec3 vertical;
        double aspect_ratio;

    public:
        Camera();
        
        Ray get_ray(double u, double v) const;

        Image get_image(int width, World world, bool antialiasing = true) const;
};

#endif