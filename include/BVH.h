#ifndef BVH_H
#define BVH_H

#include "Hittable.h"
#include "AABB.h"
#include "World.h"

class BVHNode : public Hittable
{
    public:
        std::shared_ptr<Hittable> left, right;
        AABB box;

        static std::shared_ptr<Hittable> create(const World& world);

        BVHNode(const World& world) : BVHNode(world.objects, 0, world.objects.size()) {}

        BVHNode(const std::vector<std::shared_ptr<Hittable>>& src_objects,
                size_t start, size_t end);

        virtual bool hit(const Ray &ray, double min_ray_length, double max_ray_length, HitRecord &hit_rec) const override;

        virtual void bounding_box(AABB& output_box) const override;
};

#endif