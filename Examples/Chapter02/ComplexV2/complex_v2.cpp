// Complex Version with setters and getters - clumsy version
#include <iostream>

class Complex {
public:
    double GetReal() {
        return real;
    }

    void SetReal(const double newValue) {
        real = newValue;
    }

    double GetImaginary() {
        return imaginary;
    }

    void SetImaginary(const double newValue) {
        imaginary = newValue;
    }

private:
    double real;
    double imaginary;
};

int main() {
    Complex c1, c2;
    c1.SetReal(3.0);
    c2.SetImaginary(3.0);

    c2.SetReal(c1.GetReal());
    c2.SetImaginary(c1.GetImaginary());

    std::cout << "c1 is (" << c1.GetReal() << ", " << c1.GetImaginary() << ")\n";
    std::cout << "c2 is (" << c2.GetReal() << ", " << c1.GetImaginary() << ")\n";
}