#include "ImplicitShape.h"

double Torus::get_distance(const Point3& p) const
{
    Point3 q = p;
    double x = sqrt(q.x()*q.x() + q.z()*q.z()) - radius_major;
    double y = q.y();

    return sqrt(x*x + y*y) - radius_minor;
}

void Torus::bounding_box(AABB& output_box) const
{
    double max_radius_xz = radius_major + radius_minor;
    double max_radius_y = radius_minor;
    Vec3 delta = Vec3(max_radius_xz, max_radius_y, max_radius_xz);
    output_box = AABB(-delta, delta);
}