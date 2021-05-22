#include "BVH.h"
#include "Utility.h"

#include <algorithm>

#include <stdexcept>

std::shared_ptr<Hittable> BVHNode::create(const World& world)
{
    if (world.objects.size() <= 1)
        throw std::invalid_argument("BVHNode::create: World has 1 or fewer objects.");

    return std::make_shared<BVHNode>(world);
}


BVHNode::BVHNode(const std::vector<std::shared_ptr<Hittable>>& src_objects,
                 size_t start, size_t end)
{
    // modifiable copy of src_objects
    auto objects = src_objects;

    // sorting based on random axis
    int axis = random_int(0,2);

    auto comparator = [axis](std::shared_ptr<Hittable> a, std::shared_ptr<Hittable> b)
                            {return Hittable::compare(a, b, axis);};

    size_t object_span = end - start;
    
    if (object_span == 3)
    {
        left = std::make_shared<BVHNode>(objects, start, start+2);
        right = objects[start+2];
    }
    else if (object_span == 2) {
        left = objects[start];
        right = objects[start+1];
    }
    else
    {
        std::sort(objects.begin()+start, objects.begin()+end, comparator);
        int mid = static_cast<int>(start + object_span/2);
        left = std::make_shared<BVHNode>(objects, start, mid);
        right = std::make_shared<BVHNode>(objects, mid, end);
    }

    AABB box_left, box_right;
    left->bounding_box(box_left);
    right->bounding_box(box_right);
    box = AABB::surrounding_box(box_left, box_right);
}

bool BVHNode::hit(const Ray &ray, double min_ray_length, double max_ray_length, HitRecord &hit_rec) const
{
    if (!box.hit(ray, min_ray_length, max_ray_length))
        return false;

    // The correct hit info is stored in hit_rec
    bool hit_left = left->hit(ray, min_ray_length, max_ray_length, hit_rec);
    bool hit_right = right->hit(ray, min_ray_length, hit_left ? hit_rec.ray_length : max_ray_length, hit_rec);

    return hit_left || hit_right;
}

void BVHNode::bounding_box(AABB& output_box) const
{
    output_box = box;
}