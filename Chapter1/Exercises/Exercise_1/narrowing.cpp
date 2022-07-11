// Exercise 1 - Assigns large values to integer types with uniform initialization and tests whether
// they compile
#include <iostream>
#include <limits>

int main() {
    std::cout << "The max value of unsigned char is" << std::numeric_limits<unsigned char>::max() << '\n';
#if 0
    const unsigned c1{40000000000}; // Does not compiles on 64 bit machines - doesn't fit unsigned
#endif
}