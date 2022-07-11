// A simple program to demonstrate the usage of argv argument in main function
#include <iostream>

int main(int argc, char** argv) {
    std::cout << '\n';
    for (int i = 0; i < argc; ++i) {
        std::cout << argv[i] << '\n';
    }

    return 0;
}