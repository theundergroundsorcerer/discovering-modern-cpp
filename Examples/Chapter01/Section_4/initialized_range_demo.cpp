// A small example to test initialization in range based for loop - a feature added in c++ 20
// Roughly corresponds to example in section 1.4.4.3 in the book
#include <iostream>

int main() {
    for(int primes[] = {2, 3, 5, 7, 11, 13, 17, 19}; int i : primes) {
        std::cout << i << ' ';
    }
    std::cout << std::endl;
}
