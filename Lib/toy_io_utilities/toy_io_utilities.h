// Header to for functions used to display file contents

#ifndef DISCOVERING_MODERN_CPP_TOY_IO_H
#define DISCOVERING_MODERN_CPP_TOY_IO_H
#include <string>
#include <iostream>
#include <sstream>

// A function to display contents of text file. Used in several places in Chapter 1
void DisplayTextFile(const std::string& file_name);

// Converts string to double
double StrToDouble(const std::string& str);

// Reads double from standard input source
double ReadDouble(const std::string& variable_name);

// Converts string to given var of type T
// Returns true if conversion is successful and false otherwise
// If conversion fails, the value of var is unspecified
template <typename T>
bool ConvertFromString(T& var, const std::string& str) {
    std::istringstream converter{str};
    converter >> var;

   return !(!converter || !converter.eof());
}

template <typename T>
bool ReadFromStream(T& variable, std::istream& in) {
    if(in.eof()) return false;

    std::string next_word;
    in >> next_word;

    bool success = ConvertFromString(variable, next_word);
    return success;
}


#endif