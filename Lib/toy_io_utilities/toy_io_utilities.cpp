#include "toy_io_utilities.h"
#include <fstream>
#include <sstream>

void DisplayTextFile(const std::string& file_name) {

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


// Reads double from standard input source
double StrToDouble(const std::string& str) {
    std::istringstream converter{str};
    double result;

    converter >> result;
    if(!converter || !converter.eof()) throw std::invalid_argument("Could not convert " + str + "to double");
    return result;
}

double ReadDouble(const std::string& variable_name) {
    bool success = false;

    double result;
    while(!success) {
        std::cout << "Enter " << variable_name << ": ";
        std::string next_word;
        std::cin >> next_word;
        try {
            result = StrToDouble(next_word);
            success = true;
        }
        catch(...) {
            std::cout << "Invalid input.\n";
        }
    }
    return result;
}