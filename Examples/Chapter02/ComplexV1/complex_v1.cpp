// Basic example of Complex class - uses raw member variables
#include <iostream>

class Complex {
public:
    double Real;
    double Imaginary;
};

int main() {
    Complex z, c;
    z.Real = 3.5;
    z.Imaginary = 2.0;

    // Regular access
    std::cout << "z is (" << z.Real << ", " << z.Imaginary << ")\n";

    // Access through pointer using arrow
    Complex* cPtr{&c};
    std::cout << "c is (" << cPtr->Real << ", " << cPtr->Imaginary << ")\n";
    std::cout << "Updating c...\n";
    cPtr->Real = 2.0;
    cPtr->Imaginary = -3.5;
    std::cout << "c is (" << cPtr->Real << ", " << cPtr->Imaginary << ")\n";

    // Pointer to member
    double Complex::* memberSelector = &Complex::Imaginary;
    std::cout << "z's selected member is " << z.*memberSelector << "\n";
    std::cout << "cPtr's selected member is " << cPtr->*memberSelector << '\n';

    memberSelector = &Complex::Real;
    std::cout << "z's selected member is " << z.*memberSelector << "\n";
    std::cout << "cPtr's selected member is " << cPtr->*memberSelector << '\n';

    return 0;
}