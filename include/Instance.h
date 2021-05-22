#ifndef INSTANCE_H
#define INSTANCE_H

#include <memory>

#include "Hittable.h"
#include "Transform.h"
#include "Utility.h"
#include "ImplicitShape.h"

template <class T>
class TranslationBase : public T
{
    public:
        std::shared_ptr<T> object;
        Vec3 translation;

        TranslationBase(std::shared_ptr<T> object, const Vec3& translation) : T(object->get_material()), object(object), translation(translation) {}

        bool hit(const Ray& ray, double min_ray_length, double max_ray_length, HitRecord& hit_rec) const override
        {
            Ray ray_prime(ray.origin()-translation, ray.direction());
            if (!object->hit(ray_prime, min_ray_length, max_ray_length, hit_rec))
                return false;
            
            hit_rec.p += translation;
            return true;
        }

        void bounding_box(AABB& output_box) const override
        {
            object->bounding_box(output_box);
            output_box = AABB(output_box.min() + translation, output_box.max() + translation);
        }

        std::shared_ptr<Material> get_material() const override
        {
            return object->get_material();
        }
};

/*
    Template indirection for single function specialisation.
*/
template <class T>
class TranslationImpl : public TranslationBase<T>
{
    public:
        using TranslationBase<T>::TranslationBase;
};

template<>
class TranslationImpl<ImplicitShape> : public TranslationBase<ImplicitShape>
{
    public:
        using TranslationBase::TranslationBase;

        double get_distance(const Point3& p) const override
        {
            return object->get_distance(p - translation);
        }
};

class Translation
{
    public:
        static std::shared_ptr<Shape> create(std::shared_ptr<Shape> object, const Vec3& translation)
        {
            return std::make_shared<TranslationImpl<Shape>>(object, translation);
        }

        static std::shared_ptr<ImplicitShape> create(std::shared_ptr<ImplicitShape> object, const Vec3& translation)
        {
            return std::make_shared<TranslationImpl<ImplicitShape>>(object, translation);
        }
};

template <class T>
class RotationBase : public T
{
    public:
        std::shared_ptr<T> object;
        Basis rotation;

        RotationBase(std::shared_ptr<T> object, const Basis& rotation) : 
                     T(object->get_material()), object(object), rotation(rotation) {}

        bool hit(const Ray& ray, double min_ray_length, double max_ray_length, HitRecord& hit_rec) const override
        {
            Ray ray_prime(rotation*ray.origin(), rotation*ray.direction());
            if (!object->hit(ray_prime, min_ray_length, max_ray_length, hit_rec))
                return false;

            auto rt = rotation.transpose();
            hit_rec.p = rt*hit_rec.p;
            
            hit_rec.set_face_normal(ray, rt*hit_rec.normal);
            return true;
        }

        void bounding_box(AABB& output_box) const override
        {
            object->bounding_box(output_box);
            auto rt = rotation.transpose();

            Vec3 max_pos = output_box.max();
            Vec3 min_pos = output_box.min();

            Vec3 new_min(INF);
            Vec3 new_max(-INF);
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    for (int k = 0; k < 3; k++)
                    {
                        double x = i*max_pos.x() + (1-i)*min_pos.x();
                        double y = j*max_pos.y() + (1-j)*min_pos.y();
                        double z = k*max_pos.z() + (1-k)*min_pos.z();

                        Vec3 pos(x,y,z);
                        Vec3 new_pos = rt*pos;

                        new_min = min(new_min, new_pos);
                        new_max = max(new_max, new_pos);
                    }
                }
            }
            output_box = AABB(new_min, new_max);
        }
};

/*
    Template indirection for single function specialisation.
*/
template <class T>
class RotationImpl : public RotationBase<T>
{
    public:
        using RotationBase<T>::RotationBase;
};

template<>
class RotationImpl<ImplicitShape> : public RotationBase<ImplicitShape>
{
    public:
        using RotationBase::RotationBase;

        double get_distance(const Point3& p) const override
        {
            return object->get_distance(rotation.transpose()*p);
        }

        Vec3 get_outward_normal(const Point3& p) const
        {
            Vec3 normal = object->get_outward_normal(rotation.transpose()*p);
            return rotation*normal;
        }
};

class Rotation
{
    public:
        static std::shared_ptr<Shape> create(std::shared_ptr<Shape> object, const Basis& rotation)
        {
            return std::make_shared<RotationImpl<Shape>>(object, rotation);
        }

        static std::shared_ptr<ImplicitShape> create(std::shared_ptr<ImplicitShape> object, const Basis& rotation)
        {
            return std::make_shared<RotationImpl<ImplicitShape>>(object, rotation);
        }
};

template <class T>
class InstanceBase : public T
{
    public:
        std::shared_ptr<T> object;            

        InstanceBase(std::shared_ptr<T> object, Transform transform) : T(object->get_material())
        {
            auto rotation = Rotation::create(object, transform.basis);
            this->object = Translation::create(rotation, transform.origin);
        }

        bool hit(const Ray& ray, double min_ray_length, double max_ray_length, HitRecord& hit_rec) const override
        {
            if(object->hit(ray, min_ray_length, max_ray_length, hit_rec))
                return true;
            return false;
        }

        void bounding_box(AABB& output_box) const override
        {
            object->bounding_box(output_box);
        } 
};

/*
    Template indirection for single function specialisation.
*/
template <class T>
class InstanceImpl : public InstanceBase<T>
{
    public:
        using InstanceBase<T>::InstanceBase;
};

template<>
class InstanceImpl<ImplicitShape> : public InstanceBase<ImplicitShape>
{
    public:
        using InstanceBase::InstanceBase;

        double get_distance(const Point3& p) const override
        {
            return object->get_distance(p);
        }
};

class Instance
{
    public:
        static std::shared_ptr<Shape> create(std::shared_ptr<Shape> object, const Transform& transform)
        {
            return std::make_shared<InstanceImpl<Shape>>(object, transform);
        }

        static std::shared_ptr<ImplicitShape> create(std::shared_ptr<ImplicitShape> object, const Transform& transform)
        {
            return std::make_shared<InstanceImpl<ImplicitShape>>(object, transform);
        }
};

#endif