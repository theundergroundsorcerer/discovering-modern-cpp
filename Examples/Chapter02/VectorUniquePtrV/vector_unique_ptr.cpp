// This is an alternative implementation of vector example in chapter 2 that uses unique_ptr instead of raw pointer

#include <memory>
#include <initializer_list>
#include <iostream>
#include <utility>
#include <cassert>

class Vector {
public:
    explicit Vector(std::size_t length = 0) : length{length}, elements{new double[length]} {
        for(std::size_t i = 0; i < length; ++i) {
            elements[i] = 0;
        }
    }

    Vector(const Vector& v) : length{v.length}, elements{ new double[length]} {
        for(std::size_t i = 0; i < length; ++i) {
            elements[i] = v.elements[i];
        }
    }

    auto operator=(const Vector& v) & -> Vector& {
        elements.reset(new double[v.length]);
        length = v.length;
        for(std::size_t i = 0; i < v.length; ++i) {
            elements[i] = v.elements[i];
        }

        return *this;
    }

    Vector(Vector&& v) noexcept : length{v.length}, elements{std::move(v.elements)} {
        v.length = 0;
    }

    auto operator=(Vector&& v) & noexcept -> Vector& {
        length = v.length;
        elements = std::move(v.elements);
        v.length = 0;

        return *this;
    }

    Vector(std::initializer_list<double> values) : length{values.size()}, elements{new double[values.size()]} {
        std::copy(values.begin(), values.end(), elements.get());
    }

    [[nodiscard]] auto Length() const -> std::size_t {
        return length;
    }

    auto operator[](std::size_t i) & -> double & {
        assert(i < length);
        return elements[i];
    }

    auto operator[](std::size_t i) const & -> double {
        assert(i < length);
        return elements[i];
    }

private:
    std::size_t length;
    std::unique_ptr<double[]> elements;
    friend auto operator+(const Vector& left, const Vector& right) -> Vector;
    friend auto operator<<(std::ostream& os, const Vector& v) -> std::ostream&;
};

inline auto operator+(const Vector& left, const Vector& right) -> Vector {
    assert(left.length == right.length);
    Vector result(left.length);
    for(std::size_t i = 0; i < left.length; ++i) {
        result.elements[i] = left.elements[i] + right.elements[i];
    }
}

inline auto operator<<(std::ostream& os, const Vector& v) -> std::ostream& {
    os << '(';

    if(v.length == 0) {
        os << ')';
        return os;
    }

    for(std::size_t i = 0; i < v.length-1; ++i) {
        std::cout << v.elements[i] << ' ';
    }
    std::cout << v.elements[v.length-1] << ')';

    return os;
}



auto main() -> int {
    Vector v{1,2,3};
    std::cout << "v = " << v << ". The length of v is " << v.Length() << '\n';
    Vector u;
    std::cout << "u = " << u << ". The length of u is " << u.Length() << '\n';

    std::cout << "Assigning u a new value...\n";
    u = Vector{4, 5, 6};
    std::cout << "u = " << u << '\n';
}
