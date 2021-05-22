#include "ImplicitShape.h"

void BoxRounded::bounding_box(AABB& output_box) const
{
    output_box = AABB(-half_width, half_width);
}

double BoxRounded::get_distance(const Point3& p) const
{
    Vec3 d = abs(p) - (half_width - radius);
    double outside_dist = max(d, 0).length();
    double inside_dist = std::min(max_element(d),0.0);
    return outside_dist + inside_dist - radius;
}