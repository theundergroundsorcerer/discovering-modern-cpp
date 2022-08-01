// An implementation and test of Vector class from the book using raw pointers
#include <cassert>
#include <initializer_list>
#include <iostream>
#include <algorithm>

class Vector {
public:
    using size_type = std::initializer_list<double>::size_type;

    explicit Vector(size_type size) : size{size}, elements{nullptr} {
#ifdef PRINT_FUNCTION_MESSAGES
        // prints constructor version in debug mode - in order to demonstrate copy elision
        std::cout << "Vector(int) constructor invoked!\n";
#endif
        if (size != 0) {
            elements = new double[size];
        }
    }

    Vector(const Vector &source) : Vector(source.size) {
#ifdef PRINT_FUNCTION_MESSAGES
        std::cout << "Copy constructor invoked!\n";
#endif
        assert(source.elements != nullptr);
        if (source.size != 0) {
            for (size_type i = 0; i < source.size; ++i) {
                elements[i] = source.elements[i];
            }
        }
    }

    Vector &operator=(const Vector &source) & {
#ifdef PRINT_FUNCTION_MESSAGES
        std::cout << "Move constructor called!\n";
#endif
        assert(source.size == 0 || source.elements != nullptr);
        if (this == &source) {
            return *this;
        }

        size = 0;
        delete[] elements;
        elements = nullptr;

        if (size > 0) {
            size = source.size;
            elements = new double[size];
            for (size_type i = 0; i < source.size; ++i) {
                elements[i] = source.elements[i];
            }
        }

        return *this;
    }

    Vector(Vector &&source) noexcept : Vector(source.size)  {
#ifdef PRINT_FUNCTION_MESSAGES
        std::cout << "Move constructor invoked!\n";
#endif
        assert(source.size == 0 || source.elements != nullptr);
        size = source.size;
        elements = source.elements;
        source.elements = nullptr;
        source.size = 0;
    }

    Vector &operator=(Vector &&source) & noexcept {
#ifdef PRINT_FUNCTION_MESSAGES
        std::cout << "Move assignment invoked!\n";
#endif
        assert(source.size == 0 || source.elements != nullptr);
        size = source.size;
        elements = source.elements;
        source.elements = nullptr;
        source.size = 0;
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

    Vector &operator=(std::initializer_list<double> values) {
#ifdef PRINT_FUNCTION_MESSAGES
        std::cout << "std::initializer_list assignment invoked\n";
#endif
        size = 0;
        delete[] elements;
        elements = nullptr;

        if (values.size() > 0) {
            size = values.size();
            elements = new double[size];
            std::copy(values.begin(), values.end(), elements);
        }
    }

    ~Vector() {
        size = 0;
        delete[] elements;
    }

    [[nodiscard]]
    size_type Size() const {
        return size;
    }

    double &operator[](size_type i) &{
        assert(i < size);
        assert(elements != nullptr);
        return elements[i];
    }

    double operator[](size_type i) const &{
        assert(i < size);
        assert(elements != nullptr);
        return elements[i];
    }



private:
    size_type size;
    double *elements;
    friend Vector operator+(const Vector& v1, const Vector& v2);
    friend Vector operator*(const double c, const Vector& v);
    friend std::ostream& operator<<(std::ostream& os, const Vector& v);
    friend double DotProduct(const Vector& v1, const Vector& v2);
};

inline Vector operator+(const Vector& v1, const Vector& v2) {
    assert(v1.size == 0 || v1.elements != nullptr);
    assert(v1.size == 0 || v2.elements != nullptr);
    assert(v1.size == v2.size);

    Vector result(v1.size);

    for(Vector::size_type i = 0; i < v1.size; ++i) {
        result[i] = v1[i] + v2[i];
    }

    return result;
}

inline std::ostream& operator<<(std::ostream& os, const Vector& v) {
    assert(v.size == 0 || v.elements != nullptr);
    os << "(";
    for(Vector::size_type i = 0; i < v.size-1; ++i) {
        os << v[i] << ',';
    }

    if(v.size == 0) {
        os << ')';
        return os;
    }

    os << v[v.size-1] << '}';
    return os;
}

inline Vector operator*(double c, const Vector& v) {
    assert(v.size == 0 || v.elements != nullptr);
    Vector result{v};
    for(Vector::size_type i = 0; i < result.size; ++i) {
        result[i] *= c;
    }

    return result;
}

inline double DotProduct(const Vector& v1, const Vector& v2) {
    assert(v1.size == v2.size);
    assert(v1.size == 0 || v1.elements != nullptr);
    assert(v2.size == 0 || v2.elements != nullptr);
    double result = 0;
    for(Vector::size_type i = 0; i < v1.size; ++i) {
        result += v1[i] * v2[i];
    }
    return result;
}

#ifdef PRINT_FUNCTION_MESSAGES
Vector MakeFromTemp(Vector v) {

    std::cout << "Beginning execution of MakeFromTemp...\n";

    return v;
}
#endif

int main() {
    Vector v = Vector{1,2,3} = Vector{4,5,6};
    std::cout << "v = " << v << ", v.Size() = " << v.Size() << std::endl;
    Vector u = 5 * v;
    std::cout << "5 * u = " << u <<  std::endl;
    double w = DotProduct(v, u);
    std::cout << "<" << v << ", " << u << "> = " << w << std::endl;
#ifdef PRINT_FUNCTION_MESSAGES
    std::cout << "\nCalling MakeFromTemp(Vector{1, 1, 1,1} " << std::endl;
    Vector a = MakeFromTemp(Vector{1, 1, 1,1});
    std::cout << "Assignment: a = MakeFromTemp{2, 2, 2, 2}" << std::endl;
    a = MakeFromTemp(Vector{2, 2, 2, 2});
#endif
}