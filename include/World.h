#ifndef WORLD_H
#define WORLD_H

#include <memory>
#include <vector>

#include "Hittable.h"
#include "Utility.h"

class World : public Hittable
{
    private:
        Color get_background_color(const Ray& ray) const;

    public:        
        std::vector<std::shared_ptr<Hittable>> objects;
        
        void clear();
        void add(std::shared_ptr<Hittable> object);

        Color get_ray_color(const Ray& ray, int depth) const;

        virtual bool hit(const Ray& ray, double min_ray_length, double max_ray_length, HitRecord& hit_rec) const override;

        virtual void bounding_box(AABB& output_box) const override;
};

#endif