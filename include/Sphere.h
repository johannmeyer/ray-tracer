#ifndef SPHERE_H
#define SPHERE_H

#include <memory>

#include "Material.h"
#include "Hittable.h"

class Sphere : public Hittable
{
    public:
        Point3 center;
        double radius;
        std::shared_ptr<Material> mat_ptr;

        Sphere() {}
        Sphere(Point3 center, double radius, std::shared_ptr<Material> mat_ptr) : 
                center(center), radius(radius), mat_ptr(mat_ptr) {};

        Vec3 get_outward_normal(const Point3 &p) const;
        virtual bool hit(const Ray &ray, double min_ray_length, double max_ray_length, HitRecord &hit_rec) const override;

    private:
        static void get_sphere_uv(const Point3& p, double& u, double &v);
};

#endif