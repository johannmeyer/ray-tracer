#include "AABB.h"

bool AABB::hit(const Ray& ray, double t_min, double t_max) const
{
    // Check if ray intersects in all three dimensions
    for (int i = 0; i < 3; i++)
    {
        // Precompute inverse of denominator
        double invD = 1.0/ray.direction()[i];
        double t0 = (this->min()[i] - ray.origin()[i])*invD;
        double t1 = (this->max()[i] - ray.origin()[i])*invD;

        // Ensure t0 is less than t1
        if (invD < 0.0)
            std::swap(t0, t1);
        
        // Handles camera ray clipping
        t_min = t0 > t_min ? t0 : t_min;
        t_max = t1 < t_max ? t1 : t_max;
        if (t_max <= t_min)
            return false;
    }
    return true;
}

AABB AABB::surrounding_box(const AABB& box1, const AABB& box2)
{
    Point3 new_minimum(fmin(box1.min().x(), box2.min().x()),
                        fmin(box1.min().y(), box2.min().y()),
                        fmin(box1.min().z(), box2.min().z()));
    
    Point3 new_maximum(fmax(box1.max().x(), box2.max().x()),
                        fmax(box1.max().y(), box2.max().y()),
                        fmax(box1.max().z(), box2.max().z()));

    return AABB(new_minimum, new_maximum);
}