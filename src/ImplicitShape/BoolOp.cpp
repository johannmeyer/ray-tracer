#include "ImplicitShape.h"

std::shared_ptr<Material> BoolOp::get_material() const
{
    return d1_selected ? obj1->get_material() : obj2->get_material(); 
}

void BoolOp::bounding_box(AABB& output_box) const
{
    AABB box_1, box_2;
    obj1->bounding_box(box_1);
    obj2->bounding_box(box_2);
    output_box = AABB::surrounding_box(box_1, box_2);
} 

double BoolOp::get_distance(const Point3& p) const
{
    BoolOpResult result = bool_operation(obj1->get_distance(p), obj2->get_distance(p));
    d1_selected = result.d1_selected;
    return result.dist;
}

Vec3 BoolOp::get_outward_normal(const Point3& p) const
{
    // this function can be omitted but it avoids redudant transformation calls
    // for Instances (rotation and translation) and is therefore slightly faster.
    if (d1_selected)
        return obj1->get_outward_normal(p);
    else
        return obj2->get_outward_normal(p);
}

BoolOpResult BoolOp::subtraction(double dist_1, double dist_2)
{
    return intersection(dist_1, -dist_2);
}

BoolOpResult BoolOp::intersection(double dist_1, double dist_2)
{
    BoolOpResult result;
    if (dist_1 > dist_2)
    {
        result.dist = dist_1;
        result.d1_selected = true;
    }
    else
    {
        result.dist = dist_2;
        result.d1_selected = false;
    }
    return result;
    // return std::max(dist_1, dist_2);
}

/*
    Union operation (reserved keyword union)
*/
BoolOpResult BoolOp::merge(double dist_1, double dist_2)
{
    BoolOpResult result;
    if (dist_1 < dist_2)
    {
        result.dist = dist_1;
        result.d1_selected = true;
    }
    else
    {
        result.dist = dist_2;
        result.d1_selected = false;
    }
    return result;
    // return std::min(dist_1, dist_2);
}