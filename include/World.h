#ifndef WORLD_H
#define WORLD_H

#include <memory>
#include <vector>

#include "Hittable.h"

class World : public Hittable
{
    private:
        std::vector<std::shared_ptr<Hittable>> objects;

        Color get_background_color(const Ray& ray) const;

    public:
        void clear();
        void add(std::shared_ptr<Hittable> object);

        Color get_ray_color(const Ray& ray, int depth) const;

        virtual bool hit(const Ray& ray, double min_ray_length, double max_ray_length, HitRecord& hit_rec) const override;
};

#endif