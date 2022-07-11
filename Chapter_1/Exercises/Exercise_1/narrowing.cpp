// Exercise 1 - Assigns large values to integer types with uniform initialization and tests whether
// they compile
#include <iostream>
#include <limits>


int main() {
    const long unsigned ui1{18446744073709551615ul}; // value of numeric_limits<unsigned long>::max() on 64 bit system
    std::cout << ui1 << std::endl;
#if 0
    const long unsigned ui1{18446744073709551616ul}; // will not comile
#endif
}