// Prints the sizes of intristic types to the screen.
// Displays whether chars are signed or unsigned on system
#include <iostream>
#include <limits>

int main() {
    std::cout << "Sizes of built-in types on your system:\n"
            << "Size of char is: " << sizeof(char) << " bytes\n"
            << "Size of short is: " << sizeof(short) << " bytes\n"
            << "Size of int is: " << sizeof(int) << " bytes\n"
            << "Size of long is: " << sizeof(long) << " bytes\n"
            << "Size of long long is: " << sizeof(long long) << " bytes\n"
            << "Size of float is: " << sizeof(float) << " bytes\n"
            << "Size of double is: " << sizeof(double) << " bytes\n"
            << "Size of long double is: " << sizeof(long double) << " bytes\n"
            << "Size of bool is: " << sizeof(bool) << " bytes\n"
            << "char type is " << (static_cast<int>(std::numeric_limits<char>::min()) >= 0 ? 
            "unsigned\n" : "signed\n");
        return 0;
}