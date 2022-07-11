// A small example demonstrating usage of assertions
#include <cmath>
#include <iostream>
#include <cassert>

double square_root(double x) {
    double result;

    if(x >= 0.0) {
        result = std::sqrt(x);
    }
    else {
        throw std::string{"Root from negative number!"};
    }

    assert(result >= 0);

    return result;
}

int main() {
    double x = -0.5;

    assert(x > 0.0);

    std::cout << "sqrt(x)" << square_root(x) << '\n';
}