#include "ImplicitShape.h"

void Cylinder::bounding_box(AABB& output_box) const
{
    Vec3 offset(radius, half_length, radius);
    output_box = AABB(-offset, offset);
}

double Cylinder::get_distance(const Point3& p) const
{
    double d_y = std::abs(p.y()) - half_length;
    double d_xz = std::sqrt(p.x()*p.x() + p.z()*p.z()) - radius;
    return std::min(std::max(d_xz, d_y), 0.0) + (max(Vec3(d_xz, d_y, 0),0.0)).length();
}