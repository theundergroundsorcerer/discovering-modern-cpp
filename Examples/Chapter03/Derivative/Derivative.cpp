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

}