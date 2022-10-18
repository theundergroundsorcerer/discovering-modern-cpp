// A program that demonstrates the type of *this
#include "toy_utilities.h"
#include <utility>
#include <iostream>

struct TypeDisplayer {
    void DisplayTypeInfo() & {
        std::cout << "The type of this is " << type_name<decltype(this)>() << '\n';
        std::cout << "The type of *this is " << type_name<decltype(*this)>() << std::endl;
    }

    void DisplayTypeInfo() &&  {
        std::cout << "The type of this is " << type_name<decltype(this)>() << '\n';
        std::cout << "The type of this is " << type_name<decltype(*this)>() << '\n';
    }
};

auto main() -> int {
    TypeDisplayer td1;
    td1.DisplayTypeInfo();

    TypeDisplayer{}.DisplayTypeInfo();

    TypeDisplayer const td2;
    td2.DisplayTypeInfo();
}