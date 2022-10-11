// Reads three double numbers from standard input and prints the middle value
#include "toy_utilities.h"

int main() {
    std::cout << "Enter three numbers.\n";
    double num1 = ReadDouble("first number"), num2 = ReadDouble("second number"),
    num3 = ReadDouble("third  number");

    double middle = ( (num1 <= num2 && num2 <= num3) || (num3 <= num2 && num2 <= num1 ) ) ? num2 :
                    ( ( (num1 <= num3 && num3 <= num2) || (num2 <= num3 && num3 <= num1 ) ) ? num3 : num1);
    std::cout << "The middle value is " << middle << '\n';
}
