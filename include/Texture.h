#ifndef TEXTURE_H
#define TEXTURE_H

#include "Vec3.h"
#include "Image.h"

class Texture
{
    public:
        virtual Color get_value(double u, double v, const Point3& p) const = 0;
};

class SolidColor : public Texture
{
    private:
        Color texture_color;

    public:
        SolidColor(){}
        SolidColor(Color color) : texture_color(color) {}

        virtual Color get_value(double /*u*/, double /*v*/, const Point3& /*p*/) const override
        {
            return texture_color;
        }
};

class CheckerTexture : public Texture
{
    public:
        std::shared_ptr<Texture> odd;
        std::shared_ptr<Texture> even;

        CheckerTexture() {}

        CheckerTexture(std::shared_ptr<Texture> odd, std::shared_ptr<Texture> even) :
            odd(odd), even(even) {}

        CheckerTexture(Color odd, Color even) :
            odd(std::make_shared<SolidColor>(odd)), even(std::make_shared<SolidColor>(even)) {}
        
        virtual Color get_value(double u, double v, const Point3& p) const override;
};

class ImageTexture : public Texture
{
    public:
        std::shared_ptr<Image> image_texture;

        ImageTexture() {}

        ImageTexture(const std::string& filename) : image_texture(std::make_shared<Image>(filename)) {}

        ImageTexture(std::shared_ptr<Image> image_texture) : image_texture(image_texture) {}

        virtual Color get_value(double u, double v, const Point3& p) const override;
};

#endif