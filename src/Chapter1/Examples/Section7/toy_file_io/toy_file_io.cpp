#include "toy_file_io.h"
#include <fstream>

void Display_text_file(std::string file_name) {
    std::ifstream input_file{file_name};
    if(!input_file) {
        std::cerr << "Could not open file " << file_name << '\n';
        exit(1);
    }

    char ch;
    while(input_file >> std::noskipws >> ch) {
        std::cout << ch;
    }
}