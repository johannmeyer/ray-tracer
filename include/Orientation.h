#include "Vec3.h"

struct Basis
{
    Vec3 x,y,z;

    Basis() : x(Vec3(1,0,0)), y(Vec3(0,1,0)), z(Vec3(0,0,1)) {}
    Basis(Vec3 x, Vec3 y, Vec3 z) : x(x), y(y), z(z) {}
};

class Orientation
{
    public:
        Point3 origin;
        Basis basis;

        Orientation() : origin(Point3()), basis(Basis()) {}

        Orientation(Point3 lookfrom, Point3 lookat, Vec3 vup)
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