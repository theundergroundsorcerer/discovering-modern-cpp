// A slightly modified version of c++11/derivative from the book
#include <iostream>
#include <cmath>


double sinPlusCos(double x) {
    return sin(x) + cos(x);
}

class ScFunctor {
    double operator() (double x) const {
        return sin(x) + cos(x);
    }
};

class PscFunctor {
public:
    explicit PscFunctor(double alpha) : alpha_{alpha} {}
    double operator() (double x) const {
        return sin(alpha_ * x) + cos(x);
    }
private:
    double alpha_;
};

template <typename F, typename T>
class Derivative
{
public:
    explicit Derivative(const F& f, const T& h) : f_{f}, h_{h} {}
    T operator()(const T& x) const {
        return (f_(x+h_) - f_(x)) / h_;
    }

private:
    const F& f_;
    T h_;
};

template <unsigned N, typename F, typename T>
class NthDerivative {
    using PrevDerivative = NthDerivative<N-1, F, T>;
public:
    NthDerivative(const F& f, const T& h) : fp_{f, h}, h_{h} {}
    T operator()(const T& x) const {
        if constexpr (N & 1) {
            return (fp_(x + h_) - fp_(x)) / h_;
        } else {
            return (fp_(x) - fp_(x-h_)) / h_;
        }
    }
private:
    T h_;
    PrevDerivative fp_;
};

template <typename F, typename T>
class NthDerivative<0, F, T> {
public:
    NthDerivative(const F& f, const T&) : f_{f} {}

    T operator()(const T& x) const {
        return f_(x);
    }

    const F f_;
};

template <std::size_t N>
auto deriveLambda1 = [](auto f, auto x, auto h) {
    auto prev=[&](auto y) { return deriveLambda1<N-1>(f, y, h); };
    return (prev(x+h) - prev(x)) / h;
};

template <>
auto deriveLambda1<0> = [](auto f, auto x, auto h) {
    return f(x);
};

template <std::size_t N>
auto deriveLambda2 = [](auto f, auto h) {
    if constexpr (N == 0 ) {
        return [f](double x) { return f(x); };
    } else {
        auto prev = deriveLambda2<N-1>(f, h);
        return [=](double x) {
            if constexpr (N & 1 != 0) {
                return (prev(x+h) - prev(x)) / h;
            } else {
                return (prev(x) - prev(x-h)) / h;
            }
        };
    }

};


template <typename F, typename T>
T inline finDiff(F f, const T& x, const T& h) {
    return (f(x+h)-f(x)) / h;
}


template <unsigned N, typename F, typename T>
NthDerivative<N, F, T> derive(const F& f, const T& h) {
    return NthDerivative<N, F, T>(f, h);
}





int main() {
    PscFunctor pscO{1.0};
    std::cout << finDiff(pscO, 1., 1e-8) << '\n';
    std::cout << finDiff(PscFunctor{2.0}, 1., 1e-8) << '\n';
    std::cout << finDiff(sinPlusCos, 0., 1e-8) << '\n';

    using DiffPscFunctor = Derivative<PscFunctor, double>;
    DiffPscFunctor diffPscObject{pscO, 1e-6};
    std::cout << "The derivative of sin(x) + cos(x) at 0 is " << diffPscObject(0.0) << '\n';

    using Diff2PscFunctor = Derivative<DiffPscFunctor, double>;
    Diff2PscFunctor diff2PscObject{diffPscObject, 1e-6};
    std::cout << "2nd derivative of sin(x) + cos(x) at 0 is " << diff2PscObject(0.0) << '\n';

    auto diff7PscObject = derive<7>(PscFunctor{1.0},2e-2);
    std::cout << "7th derivative of sin(x) + cos(x) at 0 is " << diff7PscObject(0.0) << '\n';

    auto diff22PscObject = derive<22>(PscFunctor{1.0}, 1e-2);
    std::cout << "22nd derivative of sin(x) + cos(x) at 0 is (not really) " << diff22PscObject(0.0) << '\n';

    auto diff3pSCLambda = derive<3>([](double x) -> double { return sin(2.0*x) + cos(x); }, 1e-4);
    std::cout << "3rd derivative of sin(2x) + cos(x) at 0 is " << diff3pSCLambda(0.0) << '\n';

    double phi = 2.5;
    auto diffSinPhi = [phi](double x) ->double
            { return finDiff([phi](double y) -> double { return(sin(phi*y));}, x,1e-4); };
    std::cout << "Derivative of sin(2.5x) at 2.0) is " << diffSinPhi(2.0) << '\n';

    auto f = [](double x) { return 2.0 * std::cos(x) + x*x; };
    std::cout << "f''(1) = " << deriveLambda1<2>(f, 1.0 , 1e-3) << std::endl;
    std::cout << "f^(5)(1) = " << deriveLambda1<5>(f, 1.0, 1e-3) << '\n';

    std::cout << "5th derivative of sin(3x) + cos(2x) at 0.0 is (not really) "
    << deriveLambda2<5>([](double x) { return sin(3.0*x) + cos(2.0*x); }, 8.32525e-5)(0.0) << '\n';
}