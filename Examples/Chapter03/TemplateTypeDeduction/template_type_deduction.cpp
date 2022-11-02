#include "toy_utilities.h"
#include <string>
#include <vector>
#include <memory>

template <typename T>
std::string l_or_r(const T& ) { return " const"; }

template <typename T>
std::string l_or_r(T&) { return " mutable";}

#define foo(T) std::cout << sizeof(T)

#define info(TPara, p) std::cout << "Type of TPara is " << type_name<TPara>() \
    << " == " << my_info<TPara>() \
    << ", is" << (std::is_lvalue_reference<TPara>::value ? "" : " no") << " lref" \
    << ", is" << (std::is_rvalue_reference<TPara>::value ? "" : " no") << " rref" \
    << ", is" << (std::is_const<TPara>::value ? "" : " not") << " const\n" \
    << "Type of p is " << type_name<decltype(p)>() \
    << " == " << my_info<decltype(p)>()  \
    << ", is" << (std::is_lvalue_reference<decltype(p)>::value ? "" : " no") << " lref" \
    << ", is" << (std::is_rvalue_reference<decltype(p)>::value ? "" : " no") << " rref"     \
    << ", is" << l_or_r(p)                                  \
    << "\n====================\n\n"

template <typename TPara>
void info2(TPara&& p) {
    std::cout << "Type of TPara is " << type_name<TPara>()
              << " === " << my_info<TPara>()
              << ", is" << (std::is_lvalue_reference<TPara>::value ? "" : " no") << " lref"
              << ", is" << (std::is_rvalue_reference<TPara>::value ? "" : " no") << " rref"
              << ", is" << (std::is_const<TPara>::value ? "" : " not") << " const\n"
              << "Type of p is " << type_name<decltype(p)>()
              << " == " << my_info<decltype(p)>()
              << ", is" << (std::is_lvalue_reference<decltype(p)>::value ? "" : " no") << " lref"
              << ", is" << (std::is_rvalue_reference<decltype(p)>::value ? "" : " no") << " rref"
              << ", is" << l_or_r(p)
              << "\n====================\n\n";
}

inline auto max(const auto& a, const auto& b) {
    return a < b ? b : a;
}

struct dummy {
    dummy& operator=(int i) {j = i; return *this;}
    int j = 8;
};

template <typename TPara>
void f1(TPara p) {
    info(TPara, p);
}

template <typename TPara>
void f2(const TPara& p) {
    info(const TPara&, p);
}

template <typename TPara>
void f3(TPara& p) {
    info(TPara, p);
}

template <typename TPara>
void f4(const TPara p) {
    info(TPara, p);
}

template <typename TPara>
void f5(TPara&& p) {
    info(TPara, p);
}

template <typename TPara>
void f6(const TPara&& p) {
    info(TPara, p);
}

template <typename TPara>
void f7(TPara&& p) {
    f5(std::forward<TPara>(p));
}

auto makeConstInt() -> const int {
    return 5;
}

auto main() -> int {
    int i = 0;
    int& j = i;
    const int& k = i;

    std::cout << "f1(TPara) invocation results:\n";
    f1(3);
    f1(i);
    f1(j);
    f1(k);

    std::unique_ptr<int> up;

    //f1(up);
    f1(std::move(up));

    std::cout << "\nf2(const TPara&) invocation results:\n";
    f2(3);
    f2(i);
    f2(j);
    f2(k);
    f2(up);

    std::cout << "\nf3(TPara&) invocation results:\n";
    f3<const int>(3);
    f3<const int&>(3);
    f3<const int&&>(3);

    f3(i);
    f3(j);
    f3(k);
    f3(up);

    std::cout << "\nf4(const TPara) invocation results:\n";
    f4(3);
    f4(i);
    f4(j);
    f4(k);
    f4(std::move(up));

    std::cout << "\nf5(TPara&&) invocation results:\n";
    f5(3);
    f5(i);
    f5(std::move(i));
    f5(j);
    f5(k);
    f5(up);
    f5(std::move(up));

    std::cout << "\nf6(const TPara&&) invocation results:\n";
    f6(3);
    // f6(i) -  i is not lvalue reference can not be passed instead of const int&&
    f6(std::move(i));
    // f6(j); same as for i
    f6(std::move(j));
    f6(std::move(k));
    f6(std::move(up));

    std::cout << "\nf7(TPara&&) (invoking f5 with std::move of the parameter within the function)\n";
    f7(3);
    f7(i);
    f7(std::move(i));
    f7(j);
    f7(k);
    f7(up);
    f7(std::move(up));

    f5(dummy{});
    std::cout << std::endl;

    return 0;
}
