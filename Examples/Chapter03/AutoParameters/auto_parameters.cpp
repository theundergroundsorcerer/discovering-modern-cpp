// Example program from Discovering Modern C++, 2nd edition
// Illustrates auto for function templates
#include <iostream>

namespace dmcpp {
    inline auto max(const auto& a, const auto& b) {
        return a < b ? b : a;
    }
}

int main() {
    std::cout << "max(3, 7) = " << dmcpp::max(3, 7) << '\n';
    std::cout << "max(3, 7.1) = " << dmcpp::max(3, 7.1) << std::endl;

    return 0;
}