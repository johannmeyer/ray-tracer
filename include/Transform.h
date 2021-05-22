#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Vec3.h"
#include "Hittable.h"

class Basis
{
    public:
        Vec3 x,y,z;

        Basis() : x(Vec3(1,0,0)), y(Vec3(0,1,0)), z(Vec3(0,0,1)) {}
        Basis(Vec3 x, Vec3 y, Vec3 z) : x(x), y(y), z(z) {}

        Basis transpose() const
        {
            return Basis(Vec3(x[0], y[0], z[0]),
                        Vec3(x[1], y[1], z[1]),
                        Vec3(x[2], y[2], z[2]));
        }

        Basis rotate(Vec3 axis, double angle) const
        {
            return Basis(x.rotate(axis,angle),
                        y.rotate(axis,angle),
                        z.rotate(axis,angle));
        }
};

inline Vec3 operator*(const Basis& A, const Vec3& v)
{
    Basis At = A.transpose();
    return Vec3(dot(At.x, v), dot(At.y, v), dot(At.z, v));
}

class Transform
{
    public:
        Point3 origin;
        Basis basis;

        Transform() : origin(Point3()), basis(Basis()) {}
        Transform(Point3 origin, Basis basis) : origin(origin), basis(basis) {}

        Transform(Point3 lookfrom, Point3 lookat, Vec3 vup)
        {
            origin = lookfrom;
            basis.x = unit_vector(lookat - lookfrom); // forward
            basis.y = unit_vector(cross(-vup, basis.x)); // to the right
            basis.z = cross(basis.x, basis.y); // down
        }

        void to_cam_basis()
        {
            basis = Basis(basis.y, basis.z, basis.x);
        }
};

#endif