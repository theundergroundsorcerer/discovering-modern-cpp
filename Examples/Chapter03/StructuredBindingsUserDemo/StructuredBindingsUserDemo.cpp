#include <iostream>

namespace dmcpp {
    class Matrix{};
    class Vector{};

    struct LUResult {
        Matrix LU;
        Vector p;
    };

    auto lu(const Matrix& A) {
        Matrix LU{A};
        Vector p{};

        return LUResult{LU, p};
    }

    template <typename T, typename U=T>
    struct SloppyComplex {
        T real;
        U imaginary;
    };
    template<typename T, typename U=T>
    class Complex {
    public:
        explicit Complex(const T &real = 0.0, const U &imaginary = 0.0) : real_{real}, imaginary_{imaginary} {}

        T const &real() const { return real_; }

        U const &imaginary() const { return imaginary_; }

        template <std::size_t N>
        [[nodiscard]] decltype(auto) get() const {
            if constexpr (N == 0) {
                return real_;
            } else {
                return imaginary_;
            }
        }
    private:
        T real_;
        U imaginary_;
    };
}

namespace std {
    template <typename T, typename U>
    struct tuple_size<dmcpp::Complex<T, U> > : public std::integral_constant<std::size_t, 2> {};

    template<std::size_t N, typename T, typename U>
    struct tuple_element<N, dmcpp::Complex<T, U> > {
        using type = decltype(std::declval<dmcpp::Complex<T, U> >().template get<N>());
    };
}

int main() {
    using namespace dmcpp;
    Matrix A;
    auto [LU, p] = lu(A);

    auto [cr, ci] = SloppyComplex<short>{4, 9};

    Complex<int, short> z{3, 7};
    auto [re, im] = z;

    std::cout << "The real part is " << re << " and the imaginary part is " << im << ".\n";
}