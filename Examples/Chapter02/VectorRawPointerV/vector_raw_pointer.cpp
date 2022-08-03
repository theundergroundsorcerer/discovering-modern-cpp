// An implementation and test of Vector class from the book using raw pointers
#include <cassert>
#include <initializer_list>
#include <iostream>
#include <algorithm>
#include <cmath>

class Vector {
public:
    using size_type = std::initializer_list<double>::size_type;


    explicit Vector(size_type size) : length{size}, elements{nullptr} {
#ifdef PRINT_FUNCTION_MESSAGES
        // prints constructor version in debug mode - in order to demonstrate copy elision
        std::cout << "Vector(int) constructor invoked!\n";
#endif
        if (size != 0) {
            elements = new double[size];
        }
    }

    Vector(const Vector &source) : Vector(source.length) {
#ifdef PRINT_FUNCTION_MESSAGES
        std::cout << "Copy constructor invoked!\n";
#endif
        assert(source.elements != nullptr);
        if (source.length != 0) {
            for (size_type i = 0; i < source.length; ++i) {
                elements[i] = source.elements[i];
            }
        }
    }

    Vector &operator=(const Vector &source) & {

#ifdef PRINT_FUNCTION_MESSAGGES
        std::cout << "Move constructor called!\n";
#endif
        assert(source.length == 0 || source.elements != nullptr);
        if (this == &source) {
            return *this;
        }

        length = 0;
        delete[] elements;
        elements = nullptr;

        if (length > 0) {
            length = source.length;
            elements = new double[length];
            for (size_type i = 0; i < source.length; ++i) {
                elements[i] = source.elements[i];
            }
        }

        return *this;
    }

    Vector(Vector &&source) noexcept : Vector(source.length)  {
#ifdef PRINT_FUNCTION_MESSAGES
        std::cout << "Move constructor invoked!\n";
#endif
        assert(source.length == 0 || source.elements != nullptr);
        length = source.length;
        elements = source.elements;
        source.elements = nullptr;
        source.length = 0;
    }

    Vector &operator=(Vector &&source) & noexcept {
#ifdef PRINT_FUNCTION_MESSAGES
        std::cout << "Move assignment invoked!\n";
#endif
        assert(source.length == 0 || source.elements != nullptr);
        length = source.length;
        elements = source.elements;
        source.elements = nullptr;
        source.length = 0;
        return *this;
    }

    Vector(std::initializer_list<double> values) : Vector(values.size()) {
#ifdef PRINT_FUNCTION_MESSAGES
        std::cout << "std::initializer_list constructor invoked\n";
#endif
        if (values.size() > 0) {
            std::copy(values.begin(), values.end(), elements);
        }
    }

    Vector &operator=(std::initializer_list<double> values) & {
#ifdef PRINT_FUNCTION_MESSAGES
        std::cout << "std::initializer_list assignment invoked\n";
#endif
        length = 0;
        delete[] elements;
        elements = nullptr;

        if (values.size() > 0) {
            length = values.size();
            elements = new double[length];
            std::copy(values.begin(), values.end(), elements);
        }

        return *this;
    }

    ~Vector() {
#ifdef PRINT_FUNCTION_MESSAGES
        std::cout << "Destructor called\n";
#endif
        length = 0;
        delete[] elements;
    }

    [[nodiscard]]
    size_type Length() const {
        return length;
    }

    double &operator[](size_type i) &{
        assert(i < length);
        assert(elements != nullptr);
        return elements[i];
    }

    double operator[](size_type i) const &{
        assert(i < length);
        assert(elements != nullptr);
        return elements[i];
    }

    [[nodiscard]]
    double Norm() const {
#ifdef PRINT_FUNCTION_MESSAGES
        std::cout << "Norm function invoked\n";
#endif
        return std::sqrt(DotProduct(*this, *this));
    }



private:
    size_type length;
    double *elements;
    friend Vector operator+(const Vector& v1, const Vector& v2);
    friend Vector operator-(const Vector& v1, const Vector& v2);
    friend Vector operator*(const double c, const Vector& v); // same as dot product
    friend double operator*(const Vector& v1, const Vector& v2);
    friend std::ostream& operator<<(std::ostream& os, const Vector& v);
    friend double DotProduct(const Vector& v1, const Vector& v2);
    friend double Norm(const Vector& v);
};

inline Vector operator+(const Vector& v1, const Vector& v2) {
    assert(v1.length == 0 || v1.elements != nullptr);
    assert(v1.length == 0 || v2.elements != nullptr);
    assert(v1.length == v2.length);

    Vector result(v1.length);

    for(Vector::size_type i = 0; i < v1.length; ++i) {
        result[i] = v1[i] + v2[i];
    }

    return result;
}

inline Vector operator-(const Vector& v1, const Vector& v2) {
    assert(v1.length == 0 || v1.elements != nullptr);
    assert(v2.length == 0 || v2.elements != nullptr);
    assert(v1.length == v2.length);

    Vector result(v1.length);
    for(Vector::size_type i = 0; i < v1.length; ++i) {
        result[i] = v1[i] - v2[i];
    }

    return result;
}

inline Vector operator*(double c, const Vector& v) {
    assert(v.length == 0 || v.elements != nullptr);
    Vector result{v};
    for(Vector::size_type i = 0; i < result.length; ++i) {
        result[i] *= c;
    }

    return result;
}

inline double operator *(const Vector& v1, const Vector& v2) {
    assert(v1.length == 0 || v1.elements != nullptr);
    assert(v2.length == 0 || v2.elements != nullptr);
    assert(v1.length == v2.length);

    double result = 0;
    for(Vector::size_type i = 0; i < v1.length; ++i) {
        result += v1[i] * v2[i];
    }

    return result;
}

inline std::ostream& operator<<(std::ostream& os, const Vector& v) {
    assert(v.length == 0 || v.elements != nullptr);
    os << "(";
    for(Vector::size_type i = 0; i < v.length - 1; ++i) {
        os << v[i] << ',';
    }

    if(v.length == 0) {
        os << ')';
        return os;
    }

    os << v[v.length - 1] << ')';
    return os;
}

inline double DotProduct(const Vector& v1, const Vector& v2) {
    return v1 * v2;
}

inline double Norm(const Vector& v) {
    return v.Norm();
}

int main() {
    Vector v{1,1,1,1};
    Vector u{1, -1, 1, -1};
    std::cout << "v = " << v << ". The length of v is " << v.Length() << '\n';
    std::cout << "u = " << u << ". The length of u is " << u.Length() << '\n';
    std::cout << v <<" + " << u << " = " << v + u << '\n';
    std::cout << v << " - " << u << " = " << v - u << '\n';
    std::cout << "<" << v <<", " << u << "> = " << DotProduct(v,u) << '\n';
    std::cout << "|" <<v << "| = " << Norm(v) << '\n';
    std::cout << "v + 2 * u = " << v + 2 * u << '\n';
}