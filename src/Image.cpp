#include "Image.h"
#include <iostream>
#include <fstream>
#include <cstring>

#include "Ascii.h"

// Helper function for indices
#define ind(r,c) (r*cols + c)


// Constructor
Image::Image(int rows, int cols) : 
                rows(rows),
                cols(cols),
                data(cols*rows, Vec3(0,0,0)){}


Image::Image(const std::string& filename)
{
    std::ifstream file;

    file.open(filename);
    if (file.fail())
    {
        std::cerr << std::strerror(errno) << std::endl;
        throw -1; // Replace with std::exception
    }

    std::string format;
    file >> format;
    assert(format == "P3");

    file >> cols;
    file >> rows;

    data.reserve(cols*rows);

    int scale;
    file >> scale;

    Color pixel_color;
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {    
            file >> pixel_color;
            this->set(r,c, pixel_color/scale);
        }
    }

    file.close();
    if (file.fail())
    {
        std::cerr << std::strerror(errno) << std::endl;
        throw -1;
    }
}

int Image::get_rows() const
{
    return rows;
}

int Image::get_cols() const
{
    return cols;
}

int Image::save_image(const std::string& filename) const
{
    std::ofstream file;

    file.open(filename);
    if (file.fail())
    {
        std::cerr << std::strerror(errno) << std::endl;
        return -1;
    }

    file << "P3\n" << std::endl 
         << cols << ' ' << rows << std::endl
         << "255" << std::endl;

    file << this->to_string();

    file.close();
    if (file.fail())
    {
        std::cerr << std::strerror(errno) << std::endl;
        return -1;
    }

    return 0;   
}

std::string Image::to_string() const
{
    std::string output;
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            Color pixel_color = this->get(r,c);
            double r = pixel_color.r();
            double g = pixel_color.g();
            double b = pixel_color.b();

            // Gamma correct (gamma = 2)
            r = std::sqrt(r);
            g = std::sqrt(g);
            b = std::sqrt(b);

            output += std::to_string(static_cast<int>(clamp(r,0,1)*255)) + ' ';
            output += std::to_string(static_cast<int>(clamp(g,0,1)*255)) + ' ';  
            output += std::to_string(static_cast<int>(clamp(b,0,1)*255)) + '\n'; 
        }
    }
    return output;
}

Vec3 Image::get(int r, int c) const
{
    return data[ind(r,c)];
}

Vec3 Image::get(double r, double c) const
{
    assert(r >= 0.0 && r <= 1.0);
    assert(c >= 0.0 && c <= 1.0);

    int int_c = static_cast<int>(c*(cols-1));
    int int_r = static_cast<int>(r*(rows-1));

    return data[ind(int_r,int_c)];
}

void Image::set(int r, int c, const Vec3& v)
{
    data[ind(r,c)] = v;
}

/*
    Converts the image to a grayscale ASCII representation of the image.
*/
Image Image::to_ascii_image()
{
    // Divide the image into a coarser grid where each block represents an ASCII character.
    const int new_rows = rows - (rows % ASCII_HEIGHT);
    const int num_ascii_per_col = rows/ASCII_HEIGHT;
    const int new_cols = cols - (cols % ASCII_WIDTH);
    const int num_ascii_per_row = cols/ASCII_WIDTH;

    Image ascii_image(new_rows, new_cols);
    for (int r = 0; r < num_ascii_per_col; r++)
    {
        for (int c = 0; c < num_ascii_per_row; c++)
        {
            // Compute mean intensity for the character block.
            Color old_color(0,0,0);
            for (int i = 0; i < ASCII_LENGTH; i++)
            {
                old_color += this->get(r*ASCII_HEIGHT + i/ASCII_WIDTH,c*ASCII_WIDTH + i%ASCII_WIDTH);
            }
            old_color /= ASCII_LENGTH;

            // Use the intensity to determine which character should be used for the 
            const int brightness = static_cast<int>((old_color.x() + old_color.y() + old_color.z())*(ASCII_TABLE_LENGTH-1)/3.0);
            const bool *character = ASCII_TABLE[brightness];
            
            // This loop can be executed in parallel and enables resuse of the above data.
            // Additionally, better cache locality than iterating in a scanline approach, 
            // since neighbouring threads access the same character's data.
            for (int i = 0; i < ASCII_LENGTH; i++)
            {
                Color pixel_color = character[i] * old_color;
                ascii_image.set(r*ASCII_HEIGHT + i/ASCII_WIDTH,c*ASCII_WIDTH + i%ASCII_WIDTH, pixel_color);
            }
        }
    }
    return ascii_image;
}

std::ostream &operator<<(std::ostream& ostream, Image& image)
{
    return ostream << image.to_string();
}