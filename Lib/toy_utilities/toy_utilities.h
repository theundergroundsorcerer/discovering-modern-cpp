// Header to for functions used to display file contents

#ifndef DISCOVERING_MODERN_CPP_TOY_IO_H
#define DISCOVERING_MODERN_CPP_TOY_IO_H
#include <string>
#include <iostream>
#include <sstream>
#include <typeinfo>
#include <string_view>

template <typename T>
constexpr auto type_name() {
    std::string_view name, prefix, suffix;
#ifdef __clang__
    name = __PRETTY_FUNCTION__;
    prefix = "auto type_name() [T = ";
    suffix = "]";
#elif defined(__GNUC__)
    name = __PRETTY_FUNCTION__;
    prefix = "constexpr auto type_name() [with T = ";
    suffix = "]";
#elif defined(_MSC_VER)
    name = __FUNCSIG__;
    prefix = "auto __cdecl type_name<";
    suffix = ">(void)";
#endif
    name.remove_prefix(prefix.size());
    name.remove_suffix(suffix.size());
    return name;
}

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

template <typename T>
struct wrap {};

template <typename T>
auto my_info() {
    return type_name<wrap<T> >();
}


#endif