// A very small example demonstrating usage of standard vector class
#include <vector>
#include <cassert>
#include <iostream>

void vector_add1(const std::vector<float>& v1, const std::vector<float>& v2, std::vector<float>& s) {
    assert(v1.size() == v2.size() && v1.size() == s.size());
    for(decltype(v1.size()) i = 0; i < v1.size(); ++i) {
        s[i] = v1[i] + v2[i];
    }
}

std::vector<float> vector_add2(const std::vector<float>& v1, const std::vector<float>& v2) {
    assert(v1.size() == v2.size());
    std::vector<float> sum(v1.size());
    for(decltype(v1.size()) i = 0; i < v1.size(); ++i) {
        sum[i] = v1[i] + v2[i];
    }

    return sum;
}


int main() {
    std::vector<float> u1{1, 2, 3}, v1{4,5,6}, sum1(3);
    vector_add1(u1, v1, sum1);
    std::cout << "The elements of u1 are: ";
    for (const auto& i : u1) {
        std::cout << i << ' ';
    }

    std::cout << "\nThe elements of v1 are: ";
    for (const auto &i : v1) {
        std::cout << i << ' ';
    }

    std::cout << "\nSum of their elements is: ";
    for(const auto &i: sum1) {
        std::cout << i << ' ';
    }
    std::cout << std::endl;

    std::vector<float> u2{10, 20, 30}, v2{40, 50, 60}, sum2 = vector_add2(u2, v2);

    std::cout << "\nThe elements of u2 are: ";
    for (const auto& i : u2) {
        std::cout << i << ' ';
    }

    std::cout << "\nThe elements of v2 are: ";
    for (const auto &i : v2) {
        std::cout << i << ' ';
    }

    std::cout << "\nSum of their elements is: ";
    for(const auto &i: sum2) {
        std::cout << i << ' ';
    }
    std::cout << std::endl;
}