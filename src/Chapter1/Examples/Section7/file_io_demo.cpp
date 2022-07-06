// A simple example demonstrating the usage of file input/output
#include <fstream>
#include <iostream>
#include "toy_file_io.h"

void Write_squares(std::string outputFileName) {
    std::ofstream square_file{outputFileName};
    if(!square_file) {
        std::cerr << "Unable to open file " << outputFileName << "for writing." << std::endl;
    }

    for(int i = 0; i < 10; ++i) {
        square_file << i << "^2 = " << i * i << '\n';
    }
}

int main() {
    std::string file_name{"squares.txt"};
    std::cout << "Writing squares...\n";
    Write_squares(file_name);
    std::cout << "Written successfully!\n";

    std::cout << "Reading squares...\n";
    Display_text_file(file_name);
    std::cout << "Done!\n";
}