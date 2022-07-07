// Demonstrates how declaration of string literal
#include <iostream>
#include <typeinfo>
using namespace std::string_literals;

int main() {
    auto name1 = "Name"s; 
    std::cout << "name1 has type " << typeid(name1).name() << '\n';
}