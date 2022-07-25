//
// Created by Yuval Khachatryan on 14/07/2022.
//

#ifndef DISCOVERINGMODERNCPP_TOY_GEOMETRY_H
#define DISCOVERINGMODERNCPP_TOY_GEOMETRY_H

#include <numbers>
#include <cmath>

using std::numbers::pi;

inline double Squared(const double n) {
    return n * n;
}

inline double Cubed(const double n) {
    return n * n * n;
}

inline double CircleCircumference(const double radius) {
    return 2.0 * pi * radius;
}

inline double CircleArea(const double radius) {
    return pi * Squared(radius);
}

inline double SphereSurfaceArea(const double radius) {
    return 4 * pi * Squared(radius);
}

inline double SphereVolume(const double radius) {
    return 4.0 / 3.0 * pi * Cubed(radius);
}

inline double CubeSurfaceArea(const double side) {
    return 6.0 * Squared(side);
}

inline double CubeVolume(const double side) {
    return Cubed(side);
}

inline double CylinderSurfaceArea(const double base_radius, const double height) {
    return 2 * CircleArea(base_radius) + CircleCircumference(base_radius) * height;
}

inline double CylinderVolume(const double base_radius, const double height) {
    return pi * Squared(base_radius) * height;
}

inline double ConeSideLength(const double base_radius, const double height) {
    return std::sqrt(Squared(base_radius) + Squared(height) );
}

inline double ConeSurfaceArea(const double base_radius, const double height) {
    return CircleArea(base_radius) + pi * base_radius * ConeSideLength(base_radius, height);
}

inline double ConeVolume(const double base_radius, const double height) {
    return CylinderVolume(base_radius, height) / 3.0;
}



#endif //DISCOVERINGMODERNCPP_TOY_GEOMETRY_H
