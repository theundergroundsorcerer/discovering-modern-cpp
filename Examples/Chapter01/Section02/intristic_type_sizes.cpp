// Prints the sizes of intristic types to the screen.
// Displays whether chars are signed or unsigned on system
#include <iostream>
#include <limits>

int main() {
    std::cout << "Sizes of built-in types on your system:\n"
            << "Length of char is: " << sizeof(char) << " bytes\n"
            << "Length of short is: " << sizeof(short) << " bytes\n"
            << "Length of int is: " << sizeof(int) << " bytes\n"
            << "Length of long is: " << sizeof(long) << " bytes\n"
            << "Length of long long is: " << sizeof(long long) << " bytes\n"
            << "Length of float is: " << sizeof(float) << " bytes\n"
            << "Length of double is: " << sizeof(double) << " bytes\n"
            << "Length of long double is: " << sizeof(long double) << " bytes\n"
            << "Length of bool is: " << sizeof(bool) << " bytes\n"
            << "char type is " << (static_cast<int>(std::numeric_limits<char>::min()) >= 0 ? 
            "unsigned\n" : "signed\n");
        return 0;
}