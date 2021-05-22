#include "ImplicitShape.h"

void BoxFrame::bounding_box(AABB& output_box) const
{
    output_box = AABB(-half_width, half_width);
}

double BoxFrame::get_distance(const Point3& p) const
{
    Vec3 q1 = abs(p) - half_width;
    Vec3 q2 = abs(q1+thickness)-thickness;
    Vec3 check1 = Vec3(q1.x(), q2.y(), q2.z());
    Vec3 check2 = Vec3(q2.x(), q1.y(), q2.z());
    Vec3 check3 = Vec3(q2.x(), q2.y(), q1.z());
    return min_element(Vec3(
        (max(check1,0.0)).length() + std::min(max_element(check1),0.0),
        (max(check2,0.0)).length() + std::min(max_element(check2),0.0),
        (max(check3,0.0)).length() + std::min(max_element(check3),0.0)));
}