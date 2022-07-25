// Exercise 5 from chapter 1 of Discovering Modern C++ 2nd edition
// Calculates the zero of f(x) = sin(5x) + cos(x) between 0 and 1 using interval arithmetic
#include <cmath>
#include <iostream>

double f(const double& x) {
    return std::sin(5*x) + std::cos(x);
}

int main() {
    double min{0.0}, max{1.0};
    double const delta{1e-12};
    double interval_length = max - min;
    double middle = 0.5;

    while(interval_length >= delta) {
        std::signbit(f(min)) == std::signbit(f(middle)) ? min = middle : max = middle;
        interval_length = max - min;
        middle = (max + min) / 2.0;
    }
    std::cout << "The root of sin(5x) + cos(x) is approximately " << middle << std::endl;
}