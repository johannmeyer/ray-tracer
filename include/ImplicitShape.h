#ifndef IMPLICIT_SHAPE_H
#define IMPLICIT_SHAPE_H

#include "Utility.h"
#include "Shape.h"
#include "Vec3.h"

class ImplicitShape : public Hittable
{
    public:
        std::shared_ptr<Material> mat_ptr;

        ImplicitShape(std::shared_ptr<Material> material) : mat_ptr(material) {}

        virtual double get_distance(const Point3& p) const = 0;

        virtual Vec3 get_outward_normal(const Point3& p) const;

        virtual bool hit(const Ray& ray, double min_ray_length, double max_ray_length, HitRecord& hit_rec) const override;

        virtual std::shared_ptr<Material> get_material() const { return mat_ptr; };
};

class Sphere : public ImplicitShape
{
    public:
        double radius;

        Sphere(double radius, std::shared_ptr<Material> mat_ptr) : 
                 ImplicitShape(mat_ptr), radius(radius) {}

        Vec3 get_outward_normal(const Point3 &p) const;
        virtual bool hit(const Ray &ray, double min_ray_length, double max_ray_length, HitRecord &hit_rec) const override;
        virtual void bounding_box(AABB& output_box) const override;
        virtual double get_distance(const Point3& p) const override;

    private:
        static void get_sphere_uv(const Point3& p, double& u, double &v);
};

class Torus : public ImplicitShape
{
    public:
        double radius_major;
        double radius_minor;

        Torus(double radius_major, double radius_minor, std::shared_ptr<Material> material) : 
              ImplicitShape(material), radius_major(radius_major), radius_minor(radius_minor) {}

        virtual double get_distance(const Point3& p) const override;

        virtual void bounding_box(AABB& output_box) const override;
};

class Box : public ImplicitShape
{
    public:
        Vec3 half_width;

        Box(Vec3 half_width, std::shared_ptr<Material> material) : ImplicitShape(material), half_width(half_width) {}

        virtual void bounding_box(AABB& output_box) const override;

        virtual double get_distance(const Point3& p) const override;
};

class BoxRounded : public ImplicitShape
{
    public:
        Vec3 half_width;
        double radius;

        BoxRounded(Vec3 half_width, double radius, std::shared_ptr<Material> material) :
                    ImplicitShape(material), half_width(half_width), radius(radius) {}

        virtual void bounding_box(AABB& output_box) const override;

        virtual double get_distance(const Point3& p) const override;
};

class BoxFrame : public ImplicitShape
{
    public:
        Vec3 half_width;
        double thickness;

        BoxFrame(Vec3 half_width, double thickness, std::shared_ptr<Material> material) :
                 ImplicitShape(material), half_width(half_width), thickness(thickness) {}
        BoxFrame(Vec3 half_width, std::shared_ptr<Material> material) : BoxFrame(half_width, 0.025, material) {}

        virtual void bounding_box(AABB& output_box) const override;

        virtual double get_distance(const Point3& p) const override;
};

class Cylinder : public ImplicitShape
{
    public:
        double half_length;
        double radius;

        Cylinder(double half_length, double radius, std::shared_ptr<Material> material) :
                    ImplicitShape(material), half_length(half_length), radius(radius) {}

        virtual void bounding_box(AABB& output_box) const override;

        virtual double get_distance(const Point3& p) const override;
};

struct BoolOpResult
{
    double dist; // the distance
    bool d1_selected; // determines if the first distance was selected
};

class BoolOp : public ImplicitShape
{
    private:
        mutable bool d1_selected; // caches the last closest object

    public:
        BoolOpResult (*bool_operation)(double, double);
        std::shared_ptr<ImplicitShape> obj1, obj2;
        
        BoolOp(BoolOpResult (*bool_operation)(double, double), std::shared_ptr<ImplicitShape> obj1, std::shared_ptr<ImplicitShape> obj2) :
                ImplicitShape(obj1->mat_ptr), bool_operation(bool_operation), obj1(obj1), obj2(obj2) {}

        virtual std::shared_ptr<Material> get_material() const override;

        virtual void bounding_box(AABB& output_box) const override;

        virtual double get_distance(const Point3& p) const override;

        virtual Vec3 get_outward_normal(const Point3& p) const override;

        static BoolOpResult subtraction(double dist_1, double dist_2);

        static BoolOpResult intersection(double dist_1, double dist_2);

        /*
            Union operation (reserved keyword union)
        */
        static BoolOpResult merge(double dist_1, double dist_2);
};


#endif