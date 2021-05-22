#ifndef RAY_H
#define RAY_H

#include "Vec3.h"

class Ray
{
    private:
        Point3 mOrigin;
        Vec3 mDirection;

    public:
        Ray() {}
        Ray(const Point3 &origin, const Vec3 &direction):
                mOrigin(origin), mDirection(unit_vector(direction)) {}
        
        Point3 origin() const { return mOrigin; }
        Vec3 direction() const { return mDirection; }

        Point3 at(double dist) const
        {
            return mOrigin + dist*mDirection;
        }
};

#endif