// Header to for functions used to display file contents

#ifndef DISCOVERING_MODERN_CPP_TOY_IO_H
#define DISCOVERING_MODERN_CPP_TOY_IO_H
#include <string>
#include <iostream>

// A function to display contents of text file. Used in several places in Chapter 1
void Display_text_file(std::string file_name);

// Reads double from standard input source
double StrToDouble(const std::string& str);

double ReadDouble(const std::string& variableName);


#endif