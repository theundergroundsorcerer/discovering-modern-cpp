// A toy program demonstrating variabe whos scope is limited to if statement
#include <iostream>

int main() {
    int a = -5;
    if (auto a = 5; a > 3) {
        std::cout << "a = " << a << '\n' << "a is larger than 3\n";
    } else {
        std::cout << "a = " << a << '\n' << "a is smaller than 3\n";
    }
    std::cout << "The value of a is actually " << a << '\n';
    return 0;
}