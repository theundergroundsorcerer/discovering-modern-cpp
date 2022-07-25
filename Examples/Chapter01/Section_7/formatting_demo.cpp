// A small program demonstrating usages of various formatting flags from <iomanip> header
#include <iomanip>
#include <iostream>
#include <numbers>

int main() {
    constexpr auto pi = std::numbers::pi;
    auto old_precision = std::cout.precision();

    std::cout << "pi is " << pi << '\n';
    std::cout << "pi is " << std::setprecision(16) << pi << '\n';
    std::cout << "pi is " << std::setw(30) << pi << '\n';
    std::cout << "pi is " << std::setfill('-') << std::left << std::setw(30) << pi << '\n';
    std::cout.setf(std::ios_base::showpos);
    std::cout << "pi is " << std::scientific << pi << '\n';
    std::cout << "pi is " << std::right << std::fixed << std::setw(30) << pi << '\n';

    std::cout << "63 octal is " << std::oct << 63 << '\n';
    std::cout << "63 hexadecimal is " << 63 << std::hex << 63 <<'\n';
    std::cout << "63 decimal is " << std::dec << 63 << '\n';
    std::cout << "pi is " << pi << '\n';

    std::cout << "pi < 3 is " << (pi < 3) << '\n';
    std::cout << "pi < 3 is " << std::boolalpha << (pi < 3) << '\n';

    // clear all formatting and revert to old precision
    std::cout.unsetf(std::ios_base::adjustfield | std::ios_base::basefield
    | std::ios_base::floatfield | std::ios_base::showpos | std::ios_base::boolalpha);
    std::cout.precision(old_precision);

    std::cout << pi << '\n';
}