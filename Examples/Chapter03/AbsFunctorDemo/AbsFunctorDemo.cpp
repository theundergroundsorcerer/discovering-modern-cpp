// A slightly modified version of abs_functor.cpp from the book
#include <complex>
#include <iostream>

namespace dmcpp {

    template<typename T>
    struct AbsFunctor {
        typedef T ResultType;
        inline T operator()(const T &x) {
            return x < T(0) ? -x : x;
        }
    };

    template<typename T>
    struct AbsFunctor<std::complex<T> > {
        typedef T ResultType;
        T operator()(const std::complex<T> &x) {
            return sqrt(real(x) * real(x) + imag(x) * imag(x));
        }
    };
#if __cplusplus >= 201402L
    template<typename T>
    decltype(auto) abs(const T &x) {
        return AbsFunctor<T>{}(x);
    }
#elif __cplusplus >= 201103L
    template <typename T>
    auto abs(const T& x) -> decltype(AbsFunctor<T>{}(x)) {
        return AbsFunctor<T>{}(x);
    }
#elif __cplusplus >= 199711L
    template <typename T>
    typename AbsFunctor<T>::ResultType abs(const T& x) {
        return AbsFunctor<T>()(x);
    }
#else
#warning "Unsupported C++ standard!"
#endif
}

auto main() -> int {
    std::cout << "abs(-7.3) = " << dmcpp::abs(-7.3) << '\n';
#if __cplusplus > 201103L
    std::cout << "abs(7-3i) = " << dmcpp::abs(std::complex<double>{3, -7}) << std::endl;
#elif
    std::complex<double> z(3, -7);
    std::cout << "abs(7-3i) = " << dmcpp::abs(z) << '\n';
#endif
    return 0;
}