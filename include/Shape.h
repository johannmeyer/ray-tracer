#ifndef SHAPE_H
#define SHAPE_H

#include "Hittable.h"
#include "Material.h"

class Shape : public Hittable
{
    public:
        std::shared_ptr<Material> mat_ptr;

        Shape(std::shared_ptr<Material> material) : mat_ptr(material) {}

        virtual std::shared_ptr<Material> get_material() const { return mat_ptr; };
};

#endif