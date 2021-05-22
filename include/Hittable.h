#ifndef HITTABLE_H
#define HITTABLE_H

#include <memory>

#include "Ray.h"
#include "Material.h"
#include "AABB.h"

class Material;

struct HitRecord
{
    Point3 p;
    Vec3 normal;
    std::shared_ptr<Material> mat_ptr;
    double ray_length;
    bool front_face;
    
    double u, v; // uv coordinates of hit

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

        virtual void bounding_box(AABB& output_box) const = 0;

        static bool compare(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b, int axis)
        {
            AABB box_a, box_b;
            a->bounding_box(box_a);
            b->bounding_box(box_b);
            return box_a.min()[axis] < box_b.min()[axis];
        }
};

#endif