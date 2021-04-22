#ifndef HITTABLE_H
#define HITTABLE_H

#include "Ray.h"

struct HitRecord
{
    Point3 p;
    Vec3 normal;
    double ray_length;
    bool front_face;

    inline void set_face_normal(const Ray& ray, const Vec3& outward_normal)
    {
        front_face = dot(ray.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class Hittable
{
    public:
        virtual bool hit(const Ray& ray, double min_ray_length, double max_ray_length, HitRecord& hit_rec) const = 0;
};

#endif