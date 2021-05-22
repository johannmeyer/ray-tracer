#ifndef AABB_H
#define AABB_H

#include "Ray.h"
#include "Vec3.h"
#include "Utility.h"

class AABB {
    public:
        Point3 minimum, maximum;

        AABB() : minimum(INF*Point3(1,1,1)), maximum(-INF*Point3(1,1,1)) {}

        AABB(const Point3& a, const Point3& b) : minimum(a), maximum(b) {}

        Point3 min() const {return minimum;}
        Point3 max() const {return maximum;}

        bool hit(const Ray& ray, double t_min, double t_max) const;

        static AABB surrounding_box(const AABB& box1, const AABB& box2);
};

#endif