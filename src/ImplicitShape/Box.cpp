#include "ImplicitShape.h"

void Box::bounding_box(AABB& output_box) const
{
    output_box = AABB(-half_width, half_width);
}

double Box::get_distance(const Point3& p) const
{
    Vec3 d = abs(p) - half_width;
    double outside_dist = max(d, 0).length();
    double inside_dist = std::min(max_element(d),0.0);
    return outside_dist + inside_dist;
}