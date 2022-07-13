// Exercise 3 - prompts for radius and height, then prints the surface area and volume
// of common 3d shapes that have the height and/or radius
#include <iostream>
#include <sstream>
#include <numbers>
#include <cmath>
#include "toy_io.h"

int main() {
    const double r = ReadDouble("radius");
    const double h = ReadDouble("height");
    const double pi = std::numbers::pi;
    const double rSquare = r * r;
    const double rCube = r * rSquare;
    const double hSquare = h * h;
    const double rSquareTimesPi = rSquare * pi;
    const double hTimesR = h * r;

    // Sphere area and volume
    const double sphereArea = 4.0 * rSquareTimesPi;
    const double sphereVolume = 4.0 / 3.0 * pi * rCube;
    std::cout << "Surface area of sphere of radius " << r << "is " << sphereArea << '\n';
    std::cout << "Sphere Volume of sphere of radius " << r << " is " << sphereVolume << '\n';

    // Cube area and volume
    const double cubeArea = 6.0 * hSquare;
    const double cubeVolume = h * hSquare;
    std::cout << "Surface area of cube of height " << h << " is " << cubeArea << '\n';
    std::cout << "Volume of cube of height " << h << " is " << cubeVolume << '\n';

    // Cylinder area and volume
    const double cylinderArea = 2.0 * rSquareTimesPi + 2 * hTimesR;
    const double cylinderVolume = pi * rSquare * h;
    std::cout << "Surface area of cylinder of height " << h << " and base radius " << r << " is " << cylinderArea << '\n';
    std::cout << "Volume of cylinder of height " << h << " and base radius " << r << " is " << cylinderVolume;

    // Cone height and volume
    const double s = std::sqrt(hSquare + rSquare); // cone side length
    const double coneSurfaceArea = pi * rSquare + pi * r * s;
    const double coneVolume = cylinderVolume / 3;
    std::cout << "Surface area of cone of base radius " << r << " and height " << h << " is " << coneSurfaceArea << '\n';
    std::cout << "Volume of cone of base radius " << r << " and height " << h << " is " << coneVolume << '\n';

    return 0;
}