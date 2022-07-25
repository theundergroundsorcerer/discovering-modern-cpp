// Exercise 1 - Assigns large values to integer types with uniform initialization and tests whether
// they compile

#include <iostream>
#include <limits>

int main() {
    const long unsigned unsigned_long_max{18446744073709551615ul}; // value of numeric_limits<unsigned long>::max() on 64 bit system
    constexpr long x =  (-2ll *(9223372036854775808ull/2));
    const long long long_min {static_cast<long int>(-9223372036854775808lu)};

    std::cout << "The maximum value of unsigned long is: " << unsigned_long_max << '\n'
        << "The minimum value of long int is: " << long_min << '\n';
}