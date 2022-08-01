// A small program demonstrating generic stream output
#include <iostream>
#include <fstream>
#include <sstream>
#include "toy_io_utilities.h"

void Write_something(std::ostream& os) {
    os << "Hi stream, did you know that 3 * 3 = " << 3 * 3 << '\n';
}

int main() {
    std::ofstream my_file{"example.txt"};
    if(!my_file) {
        std::cout << "Could not open example.txt for writing";
        exit(1);
    }

    std::stringstream my_stream;

    Write_something(std::cout);

    Write_something(my_file);
    my_file.close();
    Write_something(my_stream);


    std::cout << "my_stream is: " << my_stream.str();
    std::cout << "The contents of example.txt are:\n";
    DisplayTextFile("example.txt");
}