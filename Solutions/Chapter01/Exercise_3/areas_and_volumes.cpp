// Exercise 3 - prompts for radius and height, then prints the surface area and volume
// of common 3d shapes that have the height and/or radius
#include <iostream>
#include <numbers>
#include <cmath>
#include "toy_utilities.h"

int main() {
    const double r = ReadDouble("radius");
    const double h = ReadDouble("height");
    const double pi = std::numbers::pi;
    const double r_squared = r * r;
    const double r_cubed = r * r_squared;
    const double h_squared = h * h;
    const double r_squared_times_pi = r_squared * pi;
    const double h_times_r = h * r;

    // Sphere area and volume
    const double sphere_area = 4.0 * r_squared_times_pi;
    const double sphere_volume = 4.0 / 3.0 * pi * r_cubed;
    std::cout << "Surface area of sphere of radius " << r << "is " << sphere_area << '\n';
    std::cout << "Sphere Volume of sphere of radius " << r << " is " << sphere_volume << '\n';

    // Cubed area and volume
    const double cube_area = 6.0 * h_squared;
    const double cube_volume = h * h_squared;
    std::cout << "Surface area of cube of height " << h << " is " << cube_area << '\n';
    std::cout << "Volume of cube of height " << h << " is " << cube_volume << '\n';

    // Cylinder area and volume
    const double cylinder_area = 2.0 * r_squared_times_pi + 2 * h_times_r;
    const double cylinder_volume = pi * r_squared * h;
    std::cout << "Surface area of cylinder of height " << h << " and base radius " << r << " is " << cylinder_area << '\n';
    std::cout << "Volume of cylinder of height " << h << " and base radius " << r << " is " << cylinder_volume;

    // Cone height and volume
    const double s = std::sqrt(h_squared + r_squared); // cone side length
    const double coneSurfaceArea = pi * r_squared + pi * r * s;
    const double coneVolume = cylinder_volume / 3;
    std::cout << "Surface area of cone of base radius " << r << " and height " << h << " is " << coneSurfaceArea << '\n';
    std::cout << "Volume of cone of base radius " << r << " and height " << h << " is " << coneVolume << '\n';

    return 0;
}