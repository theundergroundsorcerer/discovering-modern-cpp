// Complex with all the constructors and access operators
#include <utility>
#include <iostream>
#include <string>
#include <cmath>
#include <numbers>
#include <fmt/format.h>
#include <sstream>
#include <algorithm>

class Complex {
public:
    Complex (double real = 0.0, double imaginary = 0.0) : real{real}, imaginary{imaginary} {}


    Complex(const Complex& complex) = default;
    Complex& operator=(const Complex& complex) = default;
    Complex(Complex&&) noexcept = default;
    Complex& operator=(Complex&&) noexcept = default;

    [[nodiscard]]
    double Real() const {
        return real;
    }

    [[nodiscard]]
    double Imaginary() const {
        return imaginary;
    }

    void SetRead(double newReal) {
        real = newReal;
    }

    void SetImaginary(double newImaginary) {
        imaginary = newImaginary;
    }

    [[nodiscard]]
    double Abs() const {
        return std::sqrt(real * real + imaginary * imaginary);
    }

    [[nodiscard]]
    double Arg() const {
        return std::atan2(imaginary, real);
    }

    [[nodiscard]]
    Complex Conjugate() const {
        return Complex{real, -imaginary};
    }

    [[nodiscard]]
    Complex Inverse() const {
        return Complex{real / Abs(), -imaginary / Abs()};
    }

private:
    double real;
    double imaginary;
    friend double Real(const Complex& c);
    friend double Real(const Complex& c);
    friend double Imaginary(const Complex& c);
    friend double Imaginary(const Complex& c);
    friend double Abs(const Complex& c);
    friend double Arg(const Complex& c);
    friend Complex Conjugate(const Complex& c);
    friend Complex Inverse(const Complex& c);
    Complex FromPolar(const double radius, const double argument);
    friend Complex operator+(const Complex& c1, const Complex& c2);
    friend Complex operator-(const Complex& c1, const Complex& c2);
    friend Complex operator*(const Complex& c1, const Complex& c2);
    friend Complex operator/(const Complex& c1, const Complex& c2);
    friend Complex operator/(const Complex& c, const double d);
};


inline double Real(const Complex& c) {
    return c.real;
}

inline double Imaginary(const Complex& c) {
    return c.imaginary;
}

inline double Abs(const Complex& c) {
    return c.Abs();
}

inline double Arg(const Complex& c) {
    return c.Arg();
}

inline Complex operator+(const Complex& c1, const Complex& c2) {
    return Complex{c1.real + c2.real, c1.imaginary + c2.imaginary };
}

inline Complex operator-(const Complex& c1, const Complex& c2) {
    return Complex{c1.real - c2.real, c1.imaginary - c2.imaginary};
}

inline Complex operator*(const Complex& c1, const Complex& c2) {
    return Complex{c1.real * c2.real - c1.imaginary * c2.imaginary,
                   c1.real * c2.imaginary + c1.imaginary * c2.real};
}

inline Complex operator/(const Complex& c1, const Complex& c2) {
    return c1 * Inverse(c2);
}

inline Complex operator/(const Complex& c, const double d) {
    return Complex{Real(c) / d, Imaginary(c) / d};
}

inline Complex Conjugate(const Complex& c) {
    return Complex{c.real, -c.imaginary};
}

inline Complex Inverse(const Complex& c) {
    return Conjugate(c) / Abs(c);
}

inline Complex FromPolar(const double radius, const double argument) {
    return Complex{radius * std::cos(argument), radius * std::sin(argument)};
}



std::ostream& operator<<(std::ostream& os, const Complex& c) {
    os << std::fixed << Real(c) << (Imaginary(c) >= 0 ? "+" : "") << Imaginary(c) << "i";
    return os;
}

template <typename T>
class ValueWrapper {
    template <typename S>
    ValueWrapper(S&& s) : value{std::forward(s)} {}

private:
    T value;
};

int main() {

}