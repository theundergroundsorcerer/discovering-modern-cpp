// A small program demonstrating usage of valarray
#include <iostream>
#include <valarray>
#include <numbers>

int main() {
    constexpr auto pi = std::numbers::pi_v<double>;
    std::valarray<double> v({pi, pi, pi, pi, pi}), w({0.0, 1 / 6.0, 1 / 4.0, 1 / 3.0, 1 / 2.0});
    std::valarray<double> s = v * w;
    std::valarray<double> t = std::sin(s);

    for(const double &x : t) {
        std::cout << x << '\n';
    }
    std::cout << std::endl;
}