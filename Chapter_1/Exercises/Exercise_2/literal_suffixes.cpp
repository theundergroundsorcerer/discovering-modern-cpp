// A small program to display types of various literals
// type_name function is from https://stackoverflow.com/a/56766138/576911
// will be replaced by source_location based version once clang supports it
#include <string_view>
#include <iostream>

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
#else
  std::cerr << "Unsupported compiler!\n";
  exit(1);
#endif
    name.remove_prefix(prefix.size());
    name.remove_suffix(suffix.size());
    return std::string{name};
}

int main() {
    auto max1{18446744073709551615ul};
    auto max2 {9223372036854775807};
    auto min1{-max2 - 1};
    std::cout << max1 << " has type " << type_name<decltype(max1)>() << '\n';
    std::cout << max2 << " has type " << type_name<decltype(max2)>() << '\n';
//    std::cout << min1 << " has type " << type_name<decltype(min1)>() << '\n';
}