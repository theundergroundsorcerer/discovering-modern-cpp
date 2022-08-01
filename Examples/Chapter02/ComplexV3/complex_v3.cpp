// First version of comlpex class with constructors
#include <iostream>

class Complex {
public:
    explicit Complex(const double real = 0, const double imaginary = 0)
    : real {real}, imaginary{imaginary} {}

    Complex(const Complex& complex)
    : real{complex.real}, imaginary{complex.imaginary} {}

    double GetReal() {
        return real;
    }

    void SetReal(double newReal) {
        real = newReal;
    }

    double GetImaginary() {
        return imaginary;
    }

    void SetImaginary(double newImaginary) {
        imaginary = newImaginary;
    }

private:
    double real;
    double imaginary;
};



int main() {
    Complex z1, z2(), z3{4}, z4 = Complex{4.0},  z5{0,1};
    std::cout << "z1 = (" << z1.GetReal() << ", " << z1.GetImaginary() << ")\n";
#if 0
    // breaks because z2 is treated as declaration of function accepting 0 arguments and not as variable defintion
    std::cout << "z2 = (" << z2.GetReal() << ", " << z2.GetImaginary() << ")\n";
#endif
}
