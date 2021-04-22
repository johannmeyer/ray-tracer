#ifndef SPHERE_H
#define SPHERE_H

#include "Hittable.h"

class Sphere : public Hittable
{
    public:
        Point3 center;
        double radius;

        Sphere() {}
        Sphere(Point3 center, double radius) : center(center), radius(radius) {};

        Vec3 get_outward_normal(const Point3 &p) const;
        virtual bool hit(const Ray &ray, double min_ray_length, double max_ray_length, HitRecord &hit_rec) const override;
};

#endif