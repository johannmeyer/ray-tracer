#ifndef MATERIAL_H
#define MATERIAL_H

#include "Hittable.h"

struct HitRecord;

class Material
{
    public:
        virtual bool scatter(const Ray& incident, const HitRecord& rec, Color& attenuation, Ray& scattered) const =0;
};

class Lambertian : public Material
{
    public:
        Color albedo;

        Lambertian(const Color& albedo) : albedo(albedo) {}

        virtual bool scatter(const Ray& incident, const HitRecord& rec, Color& attenuation, Ray& scattered) const override;
};

class Metal : public Material
{
    public:
        Color albedo;
        double roughness;

        Metal(const Color& albedo, double roughness) : albedo(albedo), roughness(roughness) {}

        virtual bool scatter(const Ray& incident, const HitRecord& rec, Color& attenuation, Ray& scattered) const override;
};

class Dielectric : public Material
{
    public:
        Color albedo;
        double ir;

        Dielectric(const Color &albedo, double index_of_refraction) : albedo(albedo), ir(index_of_refraction) {}

        virtual bool scatter(const Ray& incident, const HitRecord& rec, Color& attenuation, Ray& scattered) const override;        

    private:
        static double reflectance(double cos_theta, double eta_t);
};

#endif