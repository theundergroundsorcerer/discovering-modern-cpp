// A program that test various usages of lambda
#include <iostream>
#include <cmath>
#include <functional>


void g(auto&& f) {
    f(3);
}

struct Foo {
    int n = 0;
    void f(int a) {
        g([=, this](int k) { return n + a * k; });
        g([=, *this](int k) { return n + a * k; });
        g([&, a](int k) { n += a * k; });
    }
};


template <typename T>
auto add = [](T x, T y) -> T{return x + y;};

int main() {
    // Count with lambda
    auto counter = [x = 0]() mutable { x += 1; return x; };

    for(int i = 0; i < 10; ++i) {
        std::cout << counter() << '\n';
    }

    double phi = 2.5, xi = 0.2;
    auto pxr = [&phi, &xi](double x) { return sin(phi*x) + cos(x) * xi; };
    std::cout << pxr(std::numbers::pi / 2.0) << '\n';
    phi = 3;
    xi = 0;
    std::cout << pxr(std::numbers::pi / 2.0) << '\n';
}
