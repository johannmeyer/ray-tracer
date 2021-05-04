#include "Texture.h"

Color ImageTexture::get_value(double u, double v, const Point3& /*p*/) const 
{
    return image_texture->get(1-v,u);
}

    