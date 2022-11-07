// Solution to Exercise 3.1.12 in the book
// We use toString method instead of to_string
#include <iostream>
#include <string>
#include <sstream>

template <typename T, typename U=T>
struct Pair {
    Pair(const T& t, const U& u) : x{t}, y{u} {}
    T x;
    U y;
};

template <typename T, typename U>
std::ostream& operator<<(std::ostream& os, const Pair<T, U>& pair) {
    return os << '(' << pair.x << ", " << pair.y << ')';
}

template <typename T>
std::string toString(const T& t) {
    std::ostringstream strStream{};
    strStream << t;
    return strStream.str();
}



int main() {
    std::cout << toString(0.00000002) << '\n';
    std::cout << toString(Pair(Pair(1.01, 2.01), Pair(1, 2)));
}