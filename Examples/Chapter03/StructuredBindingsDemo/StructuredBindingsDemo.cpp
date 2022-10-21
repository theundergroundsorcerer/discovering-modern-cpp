// A slightly modified version of structured_bindings.cpp from the book
#include <iostream>
#include <array>
#include <map>
#include <tuple>
#include <utility>
#include <typeinfo>
#include <string>

using namespace std::string_literals;

namespace dmcpp {
    template <typename Container>
    auto iteratorPair(Container& container) {
        return std::make_pair(std::begin(container), std::end(container));
    }

    auto f() { return std::tuple{3, 4.2, "Huhu"s};}

    class Matrix{};
    class Vector{};

    auto lu(const Matrix& A) {
        Matrix LU{A};
        Vector p{};

        return std::tuple{LU, p};
    }
}

auto main() -> int {
    using namespace dmcpp;

    Matrix A;
    auto [LU, p] = lu(A);

    auto [a,b,c] = f();

    std::map<std::string, int> numbers {{"Zero"s, 0}, {"One"s, 1}, {"Two"s, 2} };

    typename std::map<std::string, int>::iterator first2, last2;
    tie(first2, last2) = iteratorPair(numbers);

    for (auto&& p : numbers) {
        std::cout << p.first << "->" << p.second << '\n';
    }

    for (auto& [key, value] : numbers) {
        std::cout << key << "->" << value << '\n';
    }

    std::array<int, 4> ar {3, 8, 9, 2};
    auto [fi, se, th, fo] = ar;

    std::cout << "ar reverse = {" << fo << ", " << th << ", " << se << ", " << fi << "}\n";
}