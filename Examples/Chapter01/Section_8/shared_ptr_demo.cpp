// A small program demonstrating usage of shared_ptr
#include <memory>
#include <iostream>

std::shared_ptr<double> f() {
    auto p1 = std::make_shared<double>(5.0);
    std::shared_ptr<double> p2{new double{4}}, p3 = p1;

    std::cout << "p2.use_count() = " << p2.use_count() << std::endl;
    std::cout << "p2 value:" << *p2 << '\n';
    std::cout << "p3.use_count() = " << p3.use_count() << std::endl;
    return p3;
}

int main() {
    std::shared_ptr<double> p = f();
    std::cout << "p.use_count = " << p.use_count() << std::endl;
    std::cout << "p value: " << *p << std::endl;
}