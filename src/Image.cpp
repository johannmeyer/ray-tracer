#include "Image.h"
#include <iostream>
#include <fstream>
#include <cstring>

// Helper function for indices
#define ind(r,c) (r*cols + c)

// Constructor
Image::Image(int rows, int cols) : 
                rows(rows),
                cols(cols),
                data(cols*rows, Vec3(0,0,0)){}


int Image::get_rows() const
{
    return rows;
}

int Image::get_cols() const
{
    return cols;
}

int Image::save_image(std::string filename) const
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
            Vec3 value = this->get(r,c);
            output += std::to_string(static_cast<int>(value.x()*255)) + ' ';
            output += std::to_string(static_cast<int>(value.y()*255)) + ' ';  
            output += std::to_string(static_cast<int>(value.z()*255)) + '\n'; 
        }
        
    }
    return output;
}

Vec3 Image::get(int r, int c) const
{
    return data[ind(r,c)];
}

void Image::set(int r, int c, Vec3 v)
{
    data[ind(r,c)] = v;
}

std::ostream &operator<<(std::ostream &ostream, Image &image)
{
    return ostream << image.to_string();
}